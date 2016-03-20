
#define RIGHT_FORWARD 11 //IN1
#define LEFT_FORWARD 6 //IN4
#define RIGHT_BACKWARD 10 //IN2
#define LEFT_BACKWARD 9 //IN3
#define SERVO 5

#include <Servo.h>

Servo collector;
int pos;

void wait(int milli) {
  int tim = millis();
  while (millis() - tim < milli);
}

void flash() {
  for (int i = 0; i<3; i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);  
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(300);  
  }
}

//[0, 254]
void turnRight(unsigned int degree) {
  drive_stop();
  delay(1);
  analogWrite(LEFT_FORWARD, 150);
  analogWrite(RIGHT_BACKWARD, 150);
  delay(degree*30);

  drive_stop();
  delay(1);
}

//[0, 254]
void turnLeft(unsigned int degree) {
  drive_stop();
  delay(1);
  analogWrite(RIGHT_FORWARD, 150);
  analogWrite(LEFT_BACKWARD, 150);
  delay(degree*30);

  drive_stop();
  delay(1);
}

//[-254, 254]
void drive(int spd) {
  drive_stop();
  delay(1);
  if (spd >= 0) {
    analogWrite(RIGHT_FORWARD, spd);
    analogWrite(LEFT_FORWARD, spd);
  } else {
    analogWrite(RIGHT_BACKWARD, abs(spd));
    analogWrite(LEFT_BACKWARD, abs(spd));
  }
  delay(1);
}

void drive_stop() {
  delay(1);
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, 0);
  analogWrite(LEFT_BACKWARD, 0);
  delay(1);
}

//[-254,254]
void inch(int tim) {
  delay(1);
  if (tim >= 0) {
    analogWrite(RIGHT_FORWARD, 100);
    analogWrite(LEFT_FORWARD, 100);
  } else {
    analogWrite(RIGHT_BACKWARD, 100);
    analogWrite(LEFT_BACKWARD, 100);
  }
  delay(abs(tim));
  drive_stop();
  delay(1);
}

void collect() {
  for (pos = 0; pos <= 180; pos += 1) {
    collector.write(pos);              
    delay(21);                      
  }
  delay(500);
  for (pos = 180; pos >= 0; pos -= 1) {
    collector.write(pos);              
    delay(21);                       
  }
}

void test() {
  turnRight(50);
  delay(500);
  turnLeft(50);
  delay(500);
  drive_stop();
  delay(500);
  drive(750);
  delay(500);
  drive_stop();
  delay(500);
  inch(600);
  delay(200);
  //collect();
}


void setup() {
  Serial.begin(115200);
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(SERVO, OUTPUT);
  
  pinMode(13, OUTPUT);

  //collector.attach(SERVO);
  
  drive_stop();
  //flash();
  delay(1);
  //test();
  
}

int inByte1 = 0;
int inByte2 = 0;
bool execute = false;

void loop() {

  if (Serial.available() > 0) {
    inByte1 = Serial.read();
    inByte2 = Serial.read();
    
    switch (inByte1) {
      case 'a':
        
      case 'b':

      case 'c':

      case 'd':

      default:
      
    }
  }
  if (turnLight) {
    Serial.println(inByte);
  }
  Serial.print(70);

  Serial.println("a");
  delay(1);

}
