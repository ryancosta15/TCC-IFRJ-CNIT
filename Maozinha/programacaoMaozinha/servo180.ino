#include <Servo.h>  

Servo finger;
int pos;

void setup() {
  // put your setup code here, to run once:
  finger.attach(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(pos = 0; pos <= 180; pos++) {
    finger.write(pos);
  }
  delay(2000);
  for(pos = 180; pos >= 0; pos--) {
    finger.write(pos);
  }
  delay(2000);
}
