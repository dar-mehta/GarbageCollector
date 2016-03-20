
#define RIGHT_FORWARD 11 //IN1
#define LEFT_FORWARD 6 //IN4
#define RIGHT_BACKWARD 10 //IN2
#define LEFT_BACKWARD 9 //IN3


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

//true or false
/*
void intakeOn(bool ifOn) {
  if (ifOn) {
    analogWrite(INTAKE, 200);
  } else {
    analogWrite(INTAKE, 0);
  }
}*/

void test() {
  turnRight(50);
  delay(500);
  turnLeft(50);
  delay(500);
  drive_stop();
  delay(500);
  drive(250);
  delay(500);
  drive_stop();
  delay(500);
  inch(200);
}


void setup() {
  Serial.begin(115200);
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  
  pinMode(13, OUTPUT);
  
  drive_stop();
  //flash();
  delay(1);
  test();
  
}

void loop() {
  

}
