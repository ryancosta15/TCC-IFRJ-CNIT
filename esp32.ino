#include <Servo.h>

#define RX 25
#define TX 27

Servo servo1;
Servo servo2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);
  servo1.attach(22);
  servo2.attach(23);
}

void loop() {
  // put your main code here, to run repeatedly:
  String comando = Serial2.readString();
  if (comando == "Servo1") {
    Serial.println("Recebido Servo1");
    servo1.write(180);
    delay(1000);
    servo1.write(0);
  } else if (comando == "Servo2") {
    Serial.println("Recebido Servo2");
    servo2.write(180);
    delay(1000);
    servo2.write(0);
  } else {
    Serial.println("Recebi nada!");
  }
}
