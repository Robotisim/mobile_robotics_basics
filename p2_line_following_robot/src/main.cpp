#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ir_sensor_processing.h"
#include "motor_control.h"
#include "oled_display.h"

// Global Variables
Adafruit_SSD1306 display;
int sensorData[5];
int error=0;

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  // Sensors
  setupSensors();
  // Initialize motors
  motor_setup();
  // Initialize OLED Display
  setupDisplay(display);
}

void loop() {
  readSensors(sensorData);
  error = calculateError(sensorData);
  auto pwm_values = error_motor_drive(error);
  Serial.print(pwm_values.first);Serial.print(" / ");Serial.print(pwm_values.second);Serial.print(" / ");Serial.println(error);
  displayLineFollowing(display , pwm_values.first,pwm_values.second);
}
