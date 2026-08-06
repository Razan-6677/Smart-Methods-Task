#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

const char* ssid = "RAZAN";
const char* password = "509910556"; 
const int servoPin = 18; 
Servo myServo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  myServo.attach(servoPin);
  myServo.write(90); 

  Serial.println();
  Serial.println("===============================");
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected successfully!");
  Serial.println("===============================");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin("http://task4.kesug.com/dir.txt");
    
    int httpCode = http.GET();
    
    if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      payload.trim();
      payload.toLowerCase();

      Serial.print("Direction Command: ");
      Serial.println(payload);

      if (payload == "forward") {
        myServo.write(90); 
      } 
      else if (payload == "right") {
        myServo.write(0); 
      } 
      else if (payload == "left") {
        myServo.write(180); 
      }
      else if (payload == "stop") {
        myServo.write(90); 
      }
    }
    http.end();

  } else {
    Serial.println("WiFi Disconnected! Trying to reconnect...");
  }

  delay(2000);
}
