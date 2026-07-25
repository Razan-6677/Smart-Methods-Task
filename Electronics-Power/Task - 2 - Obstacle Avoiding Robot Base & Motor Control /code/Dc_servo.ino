#include <Servo.h>

const int motor1 = 5;
const int motor2 = 6;
const int motor3 = 9;
const int motor4 = 10;

const int trigPin = 12;
const int echoPin = 11;

const int servoPin = 8;
Servo myServo;

unsigned long stateStartTime = 0;
unsigned long alternateTimer = 0;
bool isTurningRight = true;

int currentState = 1; 

void setup() {
  Serial.begin(9600);
  
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(90); 
  
  stateStartTime = millis();
}

void loop() {
  int distance = getDistance();
  
  if (distance > 0 && distance <= 10) {
    stopMotors(); 
    
    myServo.write(0);    
    delay(800);          
    myServo.write(180);  
    delay(800);
    myServo.write(90);   
    delay(600);

    moveBackward();
    delay(1000);
    turnRight();
    delay(1000);
    stopMotors();
    
    stateStartTime = millis(); 
    
    return; 
  }

  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - stateStartTime;

  if (currentState == 1) { 
    moveForward();
    if (elapsedTime >= 30000) {
      currentState = 2; 
      stateStartTime = currentTime;
    }
  } 
  else if (currentState == 2) { 
    moveBackward();
    if (elapsedTime >= 60000) {
      currentState = 3; 
      stateStartTime = currentTime;
      alternateTimer = currentTime;
    }
  } 
  else if (currentState == 3) { 
    if (currentTime - alternateTimer >= 1000) { 
      isTurningRight = !isTurningRight;
      alternateTimer = currentTime;
    }
    
    if (isTurningRight) turnRight();
    else turnLeft();

    if (elapsedTime >= 60000) {
      currentState = 1; 
      stateStartTime = currentTime;
    }
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH); 
  int d = duration * 0.034 / 2;
  
  if (d == 0) return 999; 
  return d;
}

void moveForward() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}

void moveBackward() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void turnRight() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}

void turnLeft() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void stopMotors() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}
