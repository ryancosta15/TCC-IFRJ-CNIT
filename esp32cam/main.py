from machine import reset, Pin, UART
from time import sleep
import camera
import network
import usocket
from index import html

gc.collect()

# Configuração Serial
uart = UART(0, baudrate=115200)
uart.init()
uart.write("teste") # Posteriormente substituir todos print() port uart.write()
# print() talvez possa funcionar como Serial.print()

# Configuração da câmera
flash = Pin(4, Pin.OUT)
cam = camera.init()
camera.framesize(10)

if not cam:
    print("Erro na inicialização da câmera")
    reset()

print("Câmera funcionando")

# Configuraão do WiFi
ssid = "PascomSG2.4G"
password = "ccsg2023"

network.WLAN(network.AP_IF).active(False)
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)
print("Conectando...")
sleep(3)

if wlan.isconnected():
    print("Conectado em: " + ssid)
    ip = wlan.ifconfig()[0]
    print("Endereço IP: " + ip)
else:
    print("Não conectado (Em caso de loop, use CTRL+C e depois CTRL+D)")
    sleep(3)
    reset()

# Configuração do servidor

server = usocket.socket(usocket.AF_INET, usocket.SOCK_STREAM)
server.setsockopt(usocket.SOL_SOCKET, usocket.SO_REUSEADDR, 1)
server.bind(('', 80))
server.listen(1)
print("Servidor iniciado\n")

while True:
    try:
        conn, addr = server.accept()
        print("Conexão de: " + str(addr))
        request = conn.recv(1024).decode().split(' ')[1]
        print("Requisição: " + request + "\n")
        
        if request == "/":
            conn.write(b'HTTP/1.1 200 OK\n')
            conn.write(b'Content-Type: text/html; charset=utf-8\n')
            conn.write(b'Connection: close\n')
            # conn.write(b'Content-Length:' + str(len(html)+100) + '\n\n')
            conn.write(html)
            uart.write("HTML enviado")
        if request == "/stream":
            conn.write(b"HTTP/1.1 200 OK\n")
            conn.write(b"Access-Control-Allow-Origin: *\n")
            conn.write(b"Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept\n")
            conn.write(b"Content-Type: multipart/x-mixed-replace; boundary=frame\n")
            conn.write(b"Connection: keep-alive\r\n\r\n")
            conn.setblocking(True)
            uart.write("Fazendo streaming...")

            while True:
                conn.write(b"--frame\r\n")
                conn.write(b"Content-Type: image/jpeg\r\n")
                img = camera.capture()
                conn.write(b"Content-Length: " + str(len(img)) + "\r\n\r\n")
                conn.write(img)
                conn.write(b"\r\n\r\n")
        else:
            pass
        
        conn.close()

        
    except OSError as e:
        conn.close()

