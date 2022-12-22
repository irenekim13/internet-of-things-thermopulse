#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <HCSR04.h>

ESP8266WebServer server(80); // variabel objek server
WiFiClient wifiClient;
const char *ssid = "NDAK WIFI PERAI KO DO";
const char *password = "sayangamak";
//192.168.100.91

const char *host = "http://192.168.100.52:8001/api/insert-data";   //your IP/web server address
PulseOximeter pox;
uint32_t tsLastReport = 0;
const int trigPin = D5; 
const int echoPin = D6; 

String temperature = "0";
long duration;
int distance;

void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup() {
  Serial.begin(9600);
  // Setting Mode pin 
 
  // Koneksi WiFi
  Serial.println("Conecting..... ");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi terhubung ");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  // Kode bagian Server
  server.on("/mlx-data", HTTP_POST, f_temperature);
  server.begin();
  Serial.println("Server berjalan...");

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
      Serial.println("FAILED");
      for(;;);
  } else {
      Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop() {
  pox.update();
  if (millis() - tsLastReport > 2000) {
      String s="0",d="0",postData;
      server.handleClient();
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);

      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance= duration*0.034/2;
      if(distance>0 && distance<=4){
        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(distance);
        
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        d = String(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        s = String(pox.getSpO2());
        Serial.println("%");

        HTTPClient http;
        postData = "&temperature=" + temperature + "&saturasi=" + s + "&denyut=" + d;
        http.begin(wifiClient, host);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpCode = http.POST(postData);
        String payload = http.getString();
       
        Serial.println(httpCode);
        Serial.println(payload);
        http.end();
        Serial.println("&temperature=" + temperature + "&saturasi=" + s + "&denyut=" + d);
        Serial.println("");
      }
      tsLastReport = millis();
  }
}

void f_temperature() {
  if (server.hasArg("temperature")) {
    temperature = server.arg("temperature");
    
    server.send(200, "text/plain", "Perintah sudah dilakukan, temperature = " + temperature);
  }
  else {
    server.send(200, "text/plain", "Format perintah salah / tidak ada");
  }
}

// Fungsi untuk menangani request /setpin
//void setPin() {
//  if (server.hasArg("pin") && server.hasArg("state")) {
//    int statusPin = server.arg("state").toInt();
//    // Konversi nama pin ke alamat pin
//    String namaPin = server.arg("pin");
//    static const uint8_t pinAddress[] = {16,  5,  4,  0,  2, 14, 12, 13, 15,  3,  1};
//    
//    digitalWrite(pinAddress[namaPin.substring(1).toInt()], statusPin);
//    server.send(200, "text/plain", "Perintah sudah dilakukan");
//  }
//  else {
//    server.send(200, "text/plain", "Format perintah salah / tidak ada");
//  }
//}
