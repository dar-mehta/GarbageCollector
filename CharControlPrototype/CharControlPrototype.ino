#include <Servo.h>

Servo serv;
int pos = 0;


void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(6, OUTPUT);
  serv.attach(9);
}

int inByte1 = 0;
int inByte2 = 0;


void loop() {

  if (Serial.available() > 0) {
    inByte1 = Serial.read();
    inByte2 = Serial.read();
    delay(10);


      if (inByte1 == 'A') {
        digitalWrite(13, HIGH);
        delay(400);
        digitalWrite(13, LOW);
      } else if (inByte1 == 'B') {
        digitalWrite(12, HIGH);
        delay(400);
        digitalWrite(12, LOW);
      } else if (inByte1 == 'C') {
        digitalWrite(11, HIGH);
        delay(400);
        digitalWrite(11, LOW);
      } else if (inByte1 == 'D') {
        digitalWrite(10, HIGH);
        delay(400);
        digitalWrite(10, LOW);
        
      } else if (inByte1 == 'E') {
        serv.write(90);
      } else if (inByte1 == 'F') {
        serv.write(180);
      } else if (inByte1 == 'G') {
         serv.write(0);
      }

      delay(10);
    }

  delay(10);

  

}
