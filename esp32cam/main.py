from machine import reset, Pin
from time import sleep
import camera
import network
import usocket

gc.collect()

# Configuração da câmera
flash = Pin(4, Pin.OUT)
cam = camera.init()
camera.framesize(10)

if not cam:
    print("Erro na inicialização da câmera")
    reset()

print("Câmera funcionando")

# Configuração do WiFi
ssid = "Maozinha"
password = "maozinha12345"

# Modo AP # OBRIGATÓRIO!
wifi = network.WLAN(network.AP_IF)
wifi.active(True)
wifi.config(essid = ssid, password = password)

# Modo Station
# wifi = network.WLAN(network.STA_IF)
# wifi.active(True)
# wifi.connect(ssid, password)

print("Conectando...")
sleep(3)

if wifi.isconnected() or wifi.active():
    print("Conectado em: " + ssid)
    ip = wifi.ifconfig()[0]
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
        request = conn.recv(1024).decode().split(' ')[1]

        # print("Conexão de: " + str(addr))
        # print("Requisição: " + request + "\n")

        if request == "/streamESP":
            conn.write(b"HTTP/1.1 200 OK\n")
            conn.write(b"Access-Control-Allow-Origin: *\n")
            conn.write(b"Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept\n")
            conn.write(b"Content-Type: multipart/x-mixed-replace; boundary=frame\n")
            conn.write(b"Connection: keep-alive\r\n\r\n")
            conn.setblocking(True)

            while True:
                conn.write(b"--frame\r\n")
                conn.write(b"Content-Type: image/jpeg\r\n")
                img = camera.capture()
                conn.write(b"Content-Length: " + str(len(img)) + "\r\n\r\n")
                conn.write(img)
                conn.write(b"\r\n\r\n")
        
        conn.close()

        
    except OSError as e:
        conn.close()

