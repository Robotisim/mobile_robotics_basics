#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "wifi_data_processing.h"
#include "motor_control.h"
#include "oled_display.h"

// Global Variables
int current_speed = 140;
Adafruit_SSD1306 display;

void setup() {
  // Initialize Serial
  Serial.begin(115200);s

  // Motor Setup
  motor_setup();
  // Initialize WiFi
  setupWiFi();

  // Initialize OLED Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  // Process WiFi Client Request
  processClientRequest();


  // Motor Control Based on Request
  display.clearDisplay();
  Serial.println(request);
  if (request == "forward") {
    forward(current_speed);
    drawForwardArrow();
  } else if (request == "backward") {
    reverse(current_speed);
    drawBackwardArrow();
  } else if (request == "left") {
    left(current_speed);
    drawLeftArrow();
  } else if (request == "right") {
    right(current_speed);
    drawRightArrow();
  } else if (request == "stop") {
    stop();
    drawStopCircle();
  } else if (request == "up") {
    if (current_speed < 255) {
      current_speed += 10;
    }
  } else if (request == "down") {
    if (current_speed > 0) {
      current_speed -= 10;
    }
  }
  display.display();
}
