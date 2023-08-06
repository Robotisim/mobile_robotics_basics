#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "motor_control.h"
#include "wifi_communication.h"
#include "oled_display.h"


void setup()
{
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
  setupOLED();
  

  setupWiFi();
 
 setupOLED();
}
void processData(String data)
{
  // Convert the received data to lowercase for case-insensitive comparison
  data.toLowerCase();

  // Display the received command on the OLED display
  displayCommandOnOLED(data);

  // Process the received data and call the appropriate functions
  if (data == "forward")
  {
    moveForward(currentSpeed); // Set the speed as needed (0 to 255)
  }
  else if (data == "backward")
  {
    moveBackward(currentSpeed); // Set the speed as needed (0 to 255)
  }
  else if (data == "right")
  {
    turnRight(); // Set the speed as needed (0 to 255)
  }
  else if (data == "left")
  {
    turnLeft(); // Set the speed as needed (0 to 255)
  }
  else if (data == "stop")
  {
    stopMotors();
  }
  else if (data == "up")
  {
    speedUp();
  }
  else if (data == "down")
  {
    speedDown();
  }
}

void loop()
{
  // Handle client connections
  client = server.available();
  if (!client)
    return;

  data = checkClient();
  // Process the received data
  processData(data);
  handleData(data);
 
}
