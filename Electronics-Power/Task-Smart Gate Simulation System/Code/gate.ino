#include <Servo.h>

int camStep = 8; 
int camDir = 9;  
int steps_45 = 25; 

int dcStep = 2; 
int dcDir = 3;  

Servo myServo;
int servoPin = 5;
int led = 12; 

void setup() {
  pinMode(camStep, OUTPUT);
  pinMode(camDir, OUTPUT);

  pinMode(dcStep, OUTPUT);
  pinMode(dcDir, OUTPUT);
  digitalWrite(dcDir, HIGH); 

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  myServo.attach(servoPin);
  myServo.write(0);

  delay(2000); 
}

void loop() {
  digitalWrite(led, HIGH); 
  
  digitalWrite(camDir, HIGH); 
  for(int x = 0; x < steps_45; x++) {
    digitalWrite(camStep, HIGH);
    delayMicroseconds(4000);
    digitalWrite(camStep, LOW);
    delayMicroseconds(4000);
  }
  
  digitalWrite(led, LOW); 
  delay(200);
  digitalWrite(led, HIGH);
  
  digitalWrite(camDir, LOW); 
  for(int x = 0; x < steps_45 * 2; x++) {
    digitalWrite(camStep, HIGH);
    delayMicroseconds(4000);
    digitalWrite(camStep, LOW);
    delayMicroseconds(4000);
  }
  
  digitalWrite(led, LOW); 
  delay(200);
  digitalWrite(led, HIGH);
  
  digitalWrite(camDir, HIGH); 
  for(int x = 0; x < steps_45; x++) {
    digitalWrite(camStep, HIGH);
    delayMicroseconds(4000);
    digitalWrite(camStep, LOW);
    delayMicroseconds(4000);
  }
  
  digitalWrite(led, LOW); 
  delay(1000); 

  for(int i = 0; i < 1000; i++) {
    digitalWrite(dcStep, HIGH);
    delayMicroseconds(1000); 
    digitalWrite(dcStep, LOW);
    delayMicroseconds(1000);
  }
  delay(500); 

  myServo.write(90); 
  delay(3000);         
  myServo.write(0);  

  delay(2000); 
}
