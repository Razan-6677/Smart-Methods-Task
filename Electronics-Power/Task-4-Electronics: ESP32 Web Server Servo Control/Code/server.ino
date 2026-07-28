#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "Razan";
const char* password = "123456789";

WiFiServer server(80);
Servo myServo;

int servoPin = 23;
int greenLedPin = 19;
int redLedPin = 18;

void setup() {
  Serial.begin(115200);

  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50);
  myServo.attach(servoPin);

  myServo.write(0);
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, LOW);

  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); 

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("<!DOCTYPE html><html><head><meta charset='UTF-8'><style>");
            client.print("body {text-align:center; font-family:Arial; margin-top:50px; background-color:#f4f4f9;}");
            client.print(".btn {font-size:24px; padding:15px 40px; margin:20px; cursor:pointer; border:none; border-radius:8px;}");
            client.print(".btn-open {background-color:#4CAF50; color:white; box-shadow: 0 4px #2e7d32;}");
            client.print(".btn-close {background-color:#f44336; color:white; box-shadow: 0 4px #c62828;}");
            client.print(".btn:active {box-shadow: 0 2px #666; transform: translateY(2px);}");
            client.print("</style></head><body>");
            client.print("<h1>Control Servo</h1>");
            client.print("<p><a href=\"/open\"><button class=\"btn btn-open\">Open</button></a></p>");
            client.print("<p><a href=\"/close\"><button class=\"btn btn-close\">Close</button></a></p>");
            client.print("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /open")) {
          myServo.write(90);
          digitalWrite(greenLedPin, HIGH);
          digitalWrite(redLedPin, LOW);
        }
        if (currentLine.endsWith("GET /close")) {
          myServo.write(0);
          digitalWrite(greenLedPin, LOW);
          digitalWrite(redLedPin, HIGH);
        }
      }
    }
    client.stop();
  }
}
