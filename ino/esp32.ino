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
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);
  polegar.attach(32);
  indicador.attach(33);
  medio.attach(25);
  anelar.attach(26);
  mindinho.attach(27);
  pulso.attach(14);
}

void loop() {
  // put your main code here, to run repeatedly:
  String comando = Serial2.readString();
  Serial.println(comando);
  if (comando.length() == 23) {
    int* posicoes = splitStringToArray(comando);
    Serial.println(posicoes[0]);

    Serial.println("funfando...");

    polegar.write(posicoes[0]);
    indicador.write(posicoes[1]);
    medio.write(posicoes[2]);
    anelar.write(posicoes[3]);
    mindinho.write(posicoes[4]);
    pulso.write(posicoes[5]);

    delay(5000);

    polegar.write(0);
    indicador.write(0);
    medio.write(0);
    anelar.write(0);
    mindinho.write(0);
    pulso.write(0);
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