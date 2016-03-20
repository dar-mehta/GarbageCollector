
#define RIGHT_FORWARD 11 //IN1
#define LEFT_FORWARD 6 //IN4
#define RIGHT_BACKWARD 10 //IN2
#define LEFT_BACKWARD 9 //IN3
#define COLLECTOR 3
#define SORTER 5
#define OTHERARDUINO 12

#include <Servo.h>

//for Main CPP
/*
#define TURNRIGHT A
#define TURNLEFT D
#define DRIVE G
#define DRIVESTOP K
#define INCH N
#define COLLECT P
#define TESTFUNCTION U
#define SWITCH X
#define TOPCLAW Z
*/

Servo collector;
int pos;

Servo sorter;
bool recycle = false;

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

//[0, 254], A
void turnRight(unsigned int degree) {
  drive_stop();
  delay(1);
  analogWrite(LEFT_FORWARD, 210);
  analogWrite(RIGHT_BACKWARD, 210);
  delay(degree*5);

  drive_stop();
  delay(1);
}

//[0, 254], D
void turnLeft(unsigned int degree) {
  drive_stop();
  delay(1);
  analogWrite(RIGHT_FORWARD, 210);
  analogWrite(LEFT_BACKWARD, 210);
  delay(degree*5);

  drive_stop();
  delay(1);
}

//[-254, 254], G
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

//K
void drive_stop() {
  delay(1);
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, 0);
  analogWrite(LEFT_BACKWARD, 0);
  delay(1);
}

//[-254,254], N
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

//P
void collect() {

  collector.write(250);
  delay(3590);
  collector.write(0);
  delay(4040);
  collector.write(0);
}

//U
void test() {
  turnRight(20);
  //delay(300);
  turnLeft(20);
  //delay(300);
  drive_stop();
  //delay(300);
  drive(250);
  //delay(300);
  drive_stop();
  delay(300);
  inch(600);
  //delay(200);
  //drive(-250);
  //delay (300);
  drive_stop();
  collect();
}

//X
void switch_() {
  if (recycle) {
    sorter.write(30); //one way
    recycle = false;
  } else {
    sorter.write(160); //one way
    recycle = true;
  }
}

//Z
void topclaw() {
  digitalWrite(OTHERARDUINO, HIGH);
  delay(300);
  digitalWrite(OTHERARDUINO, LOW);
  delay(1);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(COLLECTOR, OUTPUT);
  pinMode(OTHERARDUINO, OUTPUT);
  pinMode(SORTER, OUTPUT);
  
  pinMode(13, OUTPUT);

  digitalWrite(OTHERARDUINO, LOW);
  drive_stop();
  collector.attach(COLLECTOR);
  sorter.attach(SORTER);

/*
  collector.write(1800);
  delay(300);
  collector.write(0); */
  
  collector.write(95); // neutral
  sorter.write(60); //one way
  
  delay(500);         

  //topclaw();
  //delay(1000);
  //collect();
 
  //test();
  
}

int inByte1 = 0;
int inByte2 = 0;

void loop() {

  if (Serial.available() > 0) {
    inByte1 = Serial.read();
    inByte2 = Serial.read();
    
    if (inByte1 == 'A') {
      //turnRight(static_cast<int>(inByte2));
      turnRight(inByte2);
    } else if (inByte1 == 'D') {
      //turnLeft(static_cast<int>(inByte2));
      turnLeft(inByte2);
    } else if (inByte1 == 'G') {
      //drive(static_cast<int>(inByte2));
      drive(inByte2);
    } else if (inByte1 == 'K') {
      drive_stop();
    } else if (inByte1 == 'N') {
      inch(inByte2);
      //inch(static_cast<int>(inByte2));
    } else if (inByte1 == 'P') {
      collect();
    } else if (inByte1 == 'U') {
      test();
    } else if (inByte1 == 'X') {
      switch_();
    } else if (inByte1 == 'Z') {
      topclaw(); 
    }
  }
  delay(10);

}

