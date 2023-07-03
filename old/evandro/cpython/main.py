import cv2
import threading
from flask import Flask, Response, request
from index import html
from socket import gethostname, gethostbyname
import serial
import mediapipe as mp

# Configuração da detecção dos gestos
biblioteca = mp.solutions.hands
interpretador = biblioteca.Hands(max_num_hands=1)

status = {
    "dedao": "aberto",
    "indicador": "aberto",
    "medio": "aberto",
    "anelar": "aberto",
    "mindinho": "aberto"
}

statusC = {
    "dedao": "aberto",
    "indicador": "fechado",
    "medio": "fechado",
    "anelar": "fechado",
    "mindinho": "fechado"
}

statusL = {
    "dedao": "aberto",
    "indicador": "aberto",
    "medio": "fechado",
    "anelar": "fechado",
    "mindinho": "fechado"
}

statusY = {
    "dedao": "aberto",
    "indicador": "fechado",
    "medio": "fechado",
    "anelar": "fechado",
    "mindinho": "aberto"
}

statusSalvos = {"onC": statusC, "onL": statusL, "onY": statusY}

# Configuração Comunicação Serial
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

        # Mostrar janela
        # cv2.imshow('ESP32-CAM Stream', img)
        # if cv2.waitKey(1) == ord('q'):
        #     break

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
        count = 0
        while True:
            with imgGlobal:
                imgBytes = cv2.imencode('.jpg', img)[1].tobytes()

                imgRGB = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
                resultado = interpretador.process(imgRGB)
                pontosMao = resultado.multi_hand_landmarks
                altura, largura, _ = img.shape
                pontos = []

                if pontosMao:
                    for ponto in pontosMao:
                        for coordenada in ponto.landmark:
                            pontos.append((int(coordenada.x * largura), int(coordenada.y * altura)))
                        
                        dedos = [("indicador", 8), ("medio", 12), ("anelar", 16), ("mindinho", 20)]
                        if pontos:
                            status["dedao"] = "fechado" if  pontos[4][0] < pontos[3][0] else "aberto"
                            for x in dedos:
                                status[x[0]] = "aberto" if pontos[x[1]][1] < pontos[x[1]-2][1] else "fechado"
                
                for teste in statusSalvos:
                    if statusSalvos[teste] == status:
                        print(teste + '\r\n')
                        if count == 0:
                            testeEnvio = '/' + teste + '\r\n'
                            laires.write(b'' + testeEnvio.encode())
                            count+=1

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
