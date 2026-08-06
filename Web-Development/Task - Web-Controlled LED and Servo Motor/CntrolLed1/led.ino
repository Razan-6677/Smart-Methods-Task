#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

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

    http.begin("http://task4.kesug.com/t.txt");

    int httpCode = http.GET();

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        payload.trim();

        Serial.print("Command Received from Website: ");
        Serial.println(payload);

        if (payload == "1") {
          digitalWrite(ledPin, HIGH);
          Serial.println("Action: LED is ON");
        }
        else if (payload == "0") {
          digitalWrite(ledPin, LOW);
          Serial.println("Action: LED is OFF");
        }
      }
    } else {
      Serial.printf("Error fetching command: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected! Trying to reconnect...");
  }

  delay(3000);
}
