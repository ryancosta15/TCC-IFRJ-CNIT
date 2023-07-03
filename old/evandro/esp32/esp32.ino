#include <Servo.h>

#define RX 16
#define TX 17

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
} 

void loop() {
    String comando = Serial.readString();
    // Serial.println(comando);

    if (comando == "/onC\r\n") {
      // Serial.println("É o C!!!");

      dedao.write(0);
      indicador.write(180);
      medio.write(180);
      anelar.write(180);
      mindinho.write(180);
      pulso.write(90);

    } else if (comando == "/onY\r\n") {
      // Serial.println("É o Y!!!");

      dedao.write(90);
      indicador.write(180);
      medio.write(180);
      anelar.write(180);
      mindinho.write(0);
      pulso.write(0);

    } if (comando == "/onL\r\n") {
      // Serial.println("É o L!!!");

      pulso.write(0);
      dedao.write(90);
      indicador.write(0);
      medio.write(180);
      anelar.write(180);
      mindinho.write(180);

    } if (comando == "/onTchau\r\n") {
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
    } if (comando == "/on0\r\n") {

      dedao.write(0);
      indicador.write(180);
      medio.write(180);
      anelar.write(180);
      mindinho.write(180);
      pulso.write(0);

    } if (comando == "/on1\r\n") {
      pulso.write(0);
      dedao.write(0);
      indicador.write(0);
      medio.write(180);
      anelar.write(180);
      mindinho.write(180);
    } if (comando == "/on2\r\n") {
      pulso.write(0);
      dedao.write(0);
      indicador.write(0);
      medio.write(0);
      anelar.write(180);
      mindinho.write(180);
    } if (comando == "/on3\r\n") {
      pulso.write(0);
      dedao.write(0);
      indicador.write(0);
      medio.write(0);
      anelar.write(0);
      mindinho.write(180);
    } if (comando == "/on4\r\n") {
      pulso.write(0);
      dedao.write(0);
      indicador.write(0);
      medio.write(0);
      anelar.write(0);
      mindinho.write(0);
    } if (comando == "/on5\r\n") {
      pulso.write(0);
      dedao.write(90);
      indicador.write(0);
      medio.write(0);
      anelar.write(0);
      mindinho.write(0);
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