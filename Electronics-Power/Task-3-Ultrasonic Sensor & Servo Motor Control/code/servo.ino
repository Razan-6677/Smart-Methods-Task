#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 3;
const int ledPin = 13;

Servo myServo; 
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  myServo.attach(servoPin);
  myServo.write(0);
  
  digitalWrite(ledPin, LOW);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance > 0 && distance <= 10) {
    myServo.write(90);
    digitalWrite(ledPin, HIGH);
  } else {
    myServo.write(0);
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
}
