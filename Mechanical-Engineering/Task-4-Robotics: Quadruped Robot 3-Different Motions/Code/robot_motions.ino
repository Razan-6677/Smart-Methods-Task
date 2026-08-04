#include <Servo.h>

Servo leg1;
Servo leg2;
Servo leg3;
Servo leg4;

void setup() {
  leg1.attach(3);
  leg2.attach(4);
  leg3.attach(6);
  leg4.attach(7);

  leg1.write(90);
  leg2.write(90);
  leg3.write(90);
  leg4.write(90);
  delay(1000);
}

void loop() {
  forwardAndBack();
  delay(1000);

  sideTilt();
  delay(1000);

  happyDance();
  delay(1000);
}

void forwardAndBack() {
  for (int pos = 90; pos <= 120; pos += 1) {
    leg1.write(pos);
    leg3.write(pos);
    int pos2 = 210 - pos;
    leg2.write(pos2);
    leg4.write(pos2);
    delay(30);
  }

  for (int pos = 120; pos >= 60; pos -= 1) {
    leg1.write(pos);
    leg3.write(pos);
    int pos2 = 210 - pos;
    leg2.write(pos2);
    leg4.write(pos2);
    delay(30);
  }

  for (int pos = 60; pos <= 90; pos += 1) {
    leg1.write(pos);
    leg3.write(pos);
    int pos2 = 210 - pos;
    leg2.write(pos2);
    leg4.write(pos2);
    delay(30);
  }
}

void sideTilt() {
  for (int pos = 90; pos <= 110; pos += 1) {
    leg1.write(pos);
    leg2.write(pos);
    int pos2 = 180 - pos;
    leg3.write(pos2);
    leg4.write(pos2);
    delay(30);
  }

  for (int pos = 110; pos >= 70; pos -= 1) {
    leg1.write(pos);
    leg2.write(pos);
    int pos2 = 180 - pos;
    leg3.write(pos2);
    leg4.write(pos2);
    delay(30);
  }

  for (int pos = 70; pos <= 90; pos += 1) {
    leg1.write(pos);
    leg2.write(pos);
    int pos2 = 180 - pos;
    leg3.write(pos2);
    leg4.write(pos2);
    delay(30);
  }
}

void happyDance() {
  for (int pos = 90; pos <= 130; pos += 1) {
    leg1.write(pos);
    leg2.write(pos);
    leg3.write(pos);
    leg4.write(pos);
    delay(25);
  }

  for (int pos = 130; pos >= 50; pos -= 1) {
    leg1.write(pos);
    leg2.write(pos);
    leg3.write(pos);
    leg4.write(pos);
    delay(25);
  }

  for (int pos = 50; pos <= 90; pos += 1) {
    leg1.write(pos);
    leg2.write(pos);
    leg3.write(pos);
    leg4.write(pos);
    delay(25);
  }
}
