#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include "index.h"
#include <Servo.h>

const char *ssid = "Maozinha";
const char *password = "maozinha12345";

WebServer server(80);

Servo dedao;
Servo indicador;
Servo medio;
Servo anelar;
Servo mindinho;
Servo pulso;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  dedao.attach(26);
  indicador.attach(33);
  medio.attach(32);
  anelar.attach(14);
  mindinho.attach(27);
  pulso.attach(25);

  indicador.write(0);
  medio.write(0);
  anelar.write(0);
  mindinho.write(0);
  dedao.write(90);
  pulso.write(0);

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
  server.on("/onC", onC);
  server.on("/onY", onY);
  server.on("/onL", onL);
  server.on("/on0", on0);
  server.on("/on1", on1);
  server.on("/on2", on2);
  server.on("/on3", on3);
  server.on("/on4", on4);
  server.on("/on5", on5);
  server.on("/onTchau", onTchau);
  server.onNotFound(handleNotFound);

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  delay(2);
}

void handleRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

void onC() {
  server.send(201, "text/html", "Recebido!");
  dedao.write(0);
  indicador.write(180);
  medio.write(180);
  anelar.write(180);
  mindinho.write(180);
  pulso.write(90);
}
void onY() {
  server.send(201, "text/html", "Recebido!");
  dedao.write(90);
  indicador.write(180);
  medio.write(180);
  anelar.write(180);
  mindinho.write(0);
  pulso.write(0);
}
void onL() {
  server.send(201, "text/html", "Recebido!");
  pulso.write(0);
  dedao.write(90);
  indicador.write(0);
  medio.write(180);
  anelar.write(180);
  mindinho.write(180);
}
void onTchau() {
  server.send(201, "text/html", "Recebido!");
  indicador.write(0);
  medio.write(0);
  anelar.write(0);
  mindinho.write(0);
  dedao.write(90);
  pulso.write(0);

  delay(1000);

  pulso.write(0);
  delay(1000);
  pulso.write(90);
  delay(1000);
  pulso.write(0);
  delay(1000);
  pulso.write(90);
  delay(1000);
  pulso.write(0);
}
void on0() {
  server.send(201, "text/html", "Recebido!");
  dedao.write(0);
  indicador.write(180);
  medio.write(180);
  anelar.write(180);
  mindinho.write(180);
  pulso.write(0);
}
void on1() {
  server.send(201, "text/html", "Recebido!");
  pulso.write(0);
  dedao.write(0);
  indicador.write(0);
  medio.write(180);
  anelar.write(180);
  mindinho.write(180);
}
void on2() {
  server.send(201, "text/html", "Recebido!");
  pulso.write(0);
  dedao.write(0);
  indicador.write(0);
  medio.write(0);
  anelar.write(180);
  mindinho.write(180);
}
void on3() {
  server.send(201, "text/html", "Recebido!");
  pulso.write(0);
  dedao.write(0);
  indicador.write(0);
  medio.write(0);
  anelar.write(0);
  mindinho.write(180);
}
void on4() {
  server.send(201, "text/html", "Recebido!");
  pulso.write(0);
  dedao.write(0);
  indicador.write(0);
  medio.write(0);
  anelar.write(0);
  mindinho.write(0);
}
void on5() {
  server.send(201, "text/html", "Recebido!");
  pulso.write(0);
  dedao.write(90);
  indicador.write(0);
  medio.write(0);
  anelar.write(0);
  mindinho.write(0);
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