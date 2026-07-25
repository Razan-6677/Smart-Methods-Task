#define stepPin 5
#define dirPin 3
float stepAngle = 1.8;

int totalSteps1 = 1080 / stepAngle;
long delayTime1 = (2.5 * 1000000) / totalSteps1;

int totalSteps2 = 1080 / stepAngle;
long delayTime2 = (4.0 * 1000000) / totalSteps2;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {

  digitalWrite(dirPin, HIGH);
  for (int i = 0; i < totalSteps1; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime1 / 2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime1 / 2);
  }
  
  delay(1500);

  digitalWrite(dirPin, LOW);
  for (int i = 0; i < totalSteps2; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayTime2 / 2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayTime2 / 2);
  }

  delay(1500);
}
