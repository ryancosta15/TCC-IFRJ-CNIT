//BIBLIOTECAS

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Servo.h>  
#include "index.h"


//HOST
//Configura o nome da rede sem fio que será criada
const char *ssid = "Maozinha";
 
//Configura a senha de proteção da rede sem fio
// ATENÇÃO a qtd mínima de 8 caracteres da senha
const char *password = "maozinha12345";
 
WebServer server(80);

//SERVOS
Servo finger;
Servo arm;

int pos = 0;

void setup(void) {
   //PINOS
   finger.attach(26);
   arm.attach(25);
   pinMode(27,OUTPUT);
   digitalWrite(27,HIGH);
   
   
   Serial.begin(115200);

   //REDE E IP
   WiFi.softAP(ssid, password);
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("SSID: ");
   Serial.println(ssid);
   Serial.print("Endereço IP no modo AP: ");
   Serial.println(myIP);
   server.begin();

   if (MDNS.begin("esp32")) {
   Serial.println("MDNS responder started");
   }


   //HANDLE ROOT
   server.on("/", handleRoot);

   //SINAIS
   server.on("/fingerOn", fingerOn);
   server.on("/fingerOff", fingerOff);
   server.on("/armOn", armOn);
   server.on("/armOff", armOff);

   server.onNotFound(handleNotFound);

   server.begin();
   Serial.println("Servidor Iniciado");
}
 
void loop(void) {
   server.handleClient();
   delay(2);
}

void handleRoot() {
   server.send(200, "text/html", INDEX_HTML);
}


//FUNÇÕES SERVOS
void fingerOn() {
   for(pos = 0; pos <= 179; pos++) {
      finger.write(pos);
      digitalWrite(27, LOW);
      
      delay(15);
   }
   server.send(201, "text/html", "Finger ON");
}

void fingerOff() {
   for(pos = 179; pos > 0; pos--) {
      finger.write(pos);
      digitalWrite(27,HIGH);
      delay(15);
      
   }
   server.send(201, "text/html", "Finger OFF");
}

void armOn() {
   for(pos = 0; pos <= 179; pos++) {
      arm.write(pos);
      digitalWrite(27, LOW);
      delay(15);
   }
   server.send(201, "text/html", "arm ON");
}

void armOff() {
   for(pos = 179; pos > 0; pos--) {
      arm.write(pos);
      digitalWrite(27, HIGH);  
      delay(15);
   }
   server.send(201, "text/html", "arm OFF");
}

//DEBUG
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
