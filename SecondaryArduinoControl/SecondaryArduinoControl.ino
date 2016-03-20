#include <Servo.h>

Servo top;
int pos;

void setup() {
  pinMode(12, INPUT);
  pos = 0;
  top.attach(6);
  top.write(100);
}

void loop() {
  while (!digitalRead(12)) {
    delay(1);
  }
  while (digitalRead(12)) {
    delay(1);
  }
  
  top.write(150);
  delay(600);
  top.write(100);
  delay(600);
  top.write(100);
  
  delay(1);
}
