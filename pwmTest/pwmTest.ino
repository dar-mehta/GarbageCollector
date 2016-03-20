#include <Time.h>

// the setup routine runs once when you press reset:

void wait(int milli) {
  int tim = millis();
  while (millis() - tim < milli);
}

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  analogWrite(9, 250);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  wait(3000);
  
  digitalWrite(13, LOW);
  
}

int incomingByte = 250;

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    incomingByte = static_cast<int>(incomingByte);
    analogWrite(9, incomingByte);
  }
  Serial.println(incomingByte);
  delay(30);
}


/*
void turnLeft(unsigned int degree) {
  if (abs(degree) < 20) {
    analogWrite(MOTOR_LEFT, -100);
    analogWrite(MOTOR_RIGHT, 100);
    wait(degree*50);
    
  } else if (abs(degree) < 45) {

    analogWrite(MOTOR_LEFT, -180);
    analogWrite(MOTOR_RIGHT, 180);
    wait(degree*
    
  } else {

    analogWrite(MOTOR_LEFT, -250);
    analogWrite(MOTOR_RIGHT, 250);
  }
}

void turnLeft(unsigned int degree) {

  int waitTime = 
  int turnRate = 
    
}*/
