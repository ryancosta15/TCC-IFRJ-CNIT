#include <Servo.h>

#define RX 16
#define TX 17

Servo polegar;
Servo indicador;
Servo medio;
Servo anelar;
Servo mindinho;
Servo pulso;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX, TX);
  polegar.attach(32);
  indicador.attach(33);
  medio.attach(25);
  anelar.attach(26);
  mindinho.attach(27);
  pulso.attach(14);
}

void loop() {
    String comando = Serial2.readString();
    Serial.println(comando);

    if (comando == "/onC\r\n") {
      Serial.println("É o C!!!");
    } else if (comando == "/onB\r\n") {
      Serial.println("É o B!!!");
    } if (comando == "/onL\r\n") {
      Serial.println("É o L!!!");
    }
}

int* splitStringToArray(const String& string) {
  int* arr = new int[6]; // Tamanho do array é 6 (número de elementos)

  char* token = strtok(const_cast<char*>(string.c_str()), ",");
  int index = 0;

  while (token != NULL) {
    arr[index] = atoi(token);
    token = strtok(NULL, ",");
    index++;
  }

  return arr;
}