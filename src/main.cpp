#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "WiFi.h"
 
const char* ssid = "Jhelum.net [Luqman House]";
const char* password =  "7861234786";

WiFiServer server(80);

// Define pin connections & motor's states
#define ml_1 27
#define ml_2 14
#define mr_1 26
#define mr_2 25

// Define channels for LEDC functions
#define channel_l1 0
#define channel_l2 1
#define channel_r1 2
#define channel_r2 3

// Frequency for LEDC function
#define freq 5000

// Resolution for LEDC function
#define resolution 8

void setup() {
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, freq, resolution);
  ledcSetup(channel_l2, freq, resolution);
  ledcSetup(channel_r1, freq, resolution);
  ledcSetup(channel_r2, freq, resolution);

  // Attach the channels to the GPIOs
  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);
  Serial.begin(115200);
  Serial.println("Motors Starting");
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");

  // Start the server
  server.begin();
  Serial.print("Server started on IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  /*
  // Full speed forward for 3 seconds
  Serial.println("Motors FORWARD");
  // Ramp from 0 to 100% speed forward
  for (int i = 0; i <= 255; i++) {
    ledcWrite(channel_l1, 255);
    ledcWrite(channel_r1, 255);
    ledcWrite(channel_l2, i);
    ledcWrite(channel_r2, i);
    delay(20);
  }

  delay(3000);

  // Ramp from 100% to 0% speed backward
  Serial.println("Motors Reverse");
  for (int i = 255; i >= 0; i--) {
    ledcWrite(channel_l1, i);
    ledcWrite(channel_r1, i);
    ledcWrite(channel_l2, 255);
    ledcWrite(channel_r2, 255);
    delay(20);
  }
  */

  delay(3000);
}
