#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include "index.h"
#include "esp_camera.h"
#include "camera_pins.h"

const int cameraFramesPerSecond = 60;

const char *ssid = "Maozinha";
const char *password = "maozinha12345";
 
WebServer server(80);
bool status;

void setup(void) {
   Serial.begin(9600);

   // Modo AP
   WiFi.softAP(ssid, password);
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("Wifi criado com o SSID: ");
   Serial.println(ssid);
   Serial.print("Endereço IP: ");
   Serial.println(myIP);

   // Modo station
    //  WiFi.begin(ssid, password);
    //  while (WiFi.status() != WL_CONNECTED) {
    //        delay(500);
    //        Serial.print(".");
    //  }
    //  Serial.println("Wifi conectado");
    //  Serial.println("Endereço IP: ");
    //  Serial.println(WiFi.localIP());

   server.on("/", handleRoot);
   server.on("/stream", handleStream);
   server.on("/onC", onC);
   server.on("/onB", onB);
   server.on("/onL", onL);

   server.onNotFound(handleNotFound);

   camera_config_t config;
   config.ledc_channel = LEDC_CHANNEL_0;
   config.ledc_timer = LEDC_TIMER_0;
   config.pin_d0 = Y2_GPIO_NUM;
   config.pin_d1 = Y3_GPIO_NUM;
   config.pin_d2 = Y4_GPIO_NUM;
   config.pin_d3 = Y5_GPIO_NUM;
   config.pin_d4 = Y6_GPIO_NUM;
   config.pin_d5 = Y7_GPIO_NUM;
   config.pin_d6 = Y8_GPIO_NUM;
   config.pin_d7 = Y9_GPIO_NUM;
   config.pin_xclk = XCLK_GPIO_NUM;
   config.pin_pclk = PCLK_GPIO_NUM;
   config.pin_vsync = VSYNC_GPIO_NUM;
   config.pin_href = HREF_GPIO_NUM;
   config.pin_sccb_sda = SIOD_GPIO_NUM;
   config.pin_sccb_scl = SIOC_GPIO_NUM;
   config.pin_pwdn = PWDN_GPIO_NUM;
   config.pin_reset = RESET_GPIO_NUM;
   config.xclk_freq_hz = 20000000; // 10000000 ou 20000000
   config.frame_size = FRAMESIZE_VGA; // talvez SVGA
   config.pixel_format = PIXFORMAT_JPEG; // for streaming
   //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
   config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
   config.fb_location = CAMERA_FB_IN_PSRAM;
   config.jpeg_quality = 10; // 4 min e 63 max, menor é melhor qualidade
   config.fb_count = 1;

   esp_err_t status = esp_camera_init(&config);
   if (status != ESP_OK) {
      Serial.printf("Erro na inicialização da câmera");
      return;
   }
   Serial.printf("Camera funcionando");

   server.begin();
}
 
void loop(void) {
   server.handleClient();
   delay(2);
}

void handleRoot() {
   status = false;
   server.send(200, "text/html", INDEX_HTML);
}

// Letras apenas para teste
void onC() {
   Serial.print("090,090,090,090,090,090");
   server.send(201, "text/html", "Recebido!");
}
void onB() {
   Serial.print("090,090,090,090,090,090");
   server.send(201, "text/html", "Recebido!");
}
void onL() {
   Serial.print("179,179,179,179,090,179");
   server.send(201, "text/html", "Recebido!");
}

void handleStream() {
  status = true;
  WiFiClient client = server.client();

  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Content-Type: multipart/x-mixed-replace; boundary=frame");
  client.println();

  while (status) {
    server.handleClient();
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
      break;
    }

    client.printf("--frame\r\n");
    client.printf("Content-Type: image/jpeg\r\n");
    client.printf("Content-Length: %d\r\n\r\n", fb->len);
    client.write(fb->buf, fb->len);
    client.printf("\r\n");

    esp_camera_fb_return(fb);
    delay(1000 / cameraFramesPerSecond);
  }

  client.printf("--frame--\r\n");
}

void handleNotFound() {
   String message = "File Not Found\n\n";
   message += "URI: ";
   message += server.uri();
   message += "\nMethod: ";
   message += (server.method() == HTTP_GET) ? "GET" : "POST";
   message += "\nArguments: ";
   message += server.args();
   message += "\n";
   for (uint8_t i = 0; i < server.args(); i++) {
   message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
   }
   server.send(404, "text/plain", message);
}
