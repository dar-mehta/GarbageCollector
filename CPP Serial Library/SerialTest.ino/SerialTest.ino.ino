int turnLight = false;
int inByte = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}



void loop() {
  if (Serial.available() > 0) {
    inByte = Serial.read();
    digitalWrite(13, HIGH);
    turnLight = true;
  }
  if (turnLight) {
    Serial.println(inByte);
  }
  Serial.print(70);
}
