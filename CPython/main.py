import cv2
import threading
from flask import Flask, Response, request
from index import html
from socket import gethostname, gethostbyname
import serial

laires = serial.Serial('COM6', 115200)

imgGlobal = threading.Lock() # Variável para compartilhamento de imagem/vídeo para uso do OpenCV e transmissão para o site entre threads

# Configuração da stream
conn = cv2.VideoCapture("http://192.168.4.1:80/streamESP")
if not conn.isOpened():
    print("Não foi possível conectar ao stream de vídeo do ESP32-CAM")
    exit()

def threadJanela():
    global img
    while True:
        retorno, imgNova = conn.read()
        if not retorno:
            print("Não foi possível receber do stream")
            break

        with imgGlobal:
            img = imgNova.copy()

        # Começar implementação da IA para reconhecimento de gesto
        cv2.imshow('ESP32-CAM Stream', img)
        if cv2.waitKey(1) == ord('q'):
            break

    conn.release()
    cv2.destroyAllWindows()

# Configuração do servidor
server = Flask("")
@server.route('/')
def handleRoot():
    def root():
        yield(html.replace("IP_PYTHON", gethostbyname(gethostname())))

    return Response(root(), mimetype='text/html; charset=utf-8')

@server.route('/streamPython')
def streamPython():
    def stream():
        while True:
            with imgGlobal:
                imgBytes = cv2.imencode('.jpg', img)[1].tobytes()

            yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + imgBytes + b'\r\n')

    return Response(stream(), mimetype='multipart/x-mixed-replace; boundary=frame')

@server.route("/<path>")
def comandoPath(path):
    print(path + '\r\n')
    pathNovo = '/' + path + '\r\n'
    laires.write(b'' + pathNovo.encode())
    return Response((yield(b'Recebido')), mimetype='text/html')

# Início
threading.Thread(target=threadJanela).start()
server.run(host='0.0.0.0', port=8000)
