#define MOTOR_LEFT 9
#define MOTOR_RIGHT 10
#define INTAKE 6

void wait(int milli) {
  int tim = millis();
  while (millis() - tim < milli);
}

//[0, 254]
void turnRight(unsigned int degree) {

  analogWrite(MOTOR_LEFT, 150);
  analogWrite(MOTOR_RIGHT, -150);
  wait(degree*30);

  analogWrite(MOTOR_LEFT, 0);
  analogWrite(MOTOR_RIGHT, 0);
}

//[0, 254]
void turnLeft(unsigned int degree) {

  analogWrite(MOTOR_LEFT, -150);
  analogWrite(MOTOR_RIGHT, 150);
  wait(degree*30);

  analogWrite(MOTOR_LEFT, 0);
  analogWrite(MOTOR_RIGHT, 0);
}

//[-254, 254]
void drive(int spd) {
  analogWrite(MOTOR_LEFT, spd);
  analogWrite(MOTOR_RIGHT, spd);
}

//[-254,254]
void inch(int tim) {
  if (tim >= 0) {
    analogWrite(MOTOR_LEFT, 100);
    analogWrite(MOTOR_RIGHT, 100);
  } else {
    analogWrite(MOTOR_LEFT, -100);
    analogWrite(MOTOR_RIGHT, -100);
  }
  wait(abs(tim));
}

//true or false
void intakeOn(bool ifOn) {
  if (ifOn) {
    analogWrite(INTAKE, 200);
  } else {
    analogWrite(INTAKE, 0);
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
  pinMode(INTAKE, OUTPUT);

  drive(0);
  intakeOn(false);
  
}

void loop() {
  

}
