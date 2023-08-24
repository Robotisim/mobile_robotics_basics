#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "motor_control.h"
#include "pi_controller.h"
#include "wifi_udp.h"
#include "oled_display.h"

void setup()
{
  connectToWifi();
  setupMotors();
  start_robot();
  setupOLED();
}

void loop()
{
  // Get the current time in milliseconds
  read_sensor_values();
  unsigned long currentMillis = millis();
  // if (udp.parsePacket())

  // {
  //   // Check if it's time to send data (every 1 second)
  //   if (currentMillis - previousMillis >= interval)
  //   {
  //     // Update the previous time to the current time
  //     previousMillis = currentMillis; // If we recieve any packet
  //     parseUdpMessage();
  //   }
  // }
  // else
  // {
  read_sensor_values();
  // Send the sensor values to the server
  send_sensor_values_over_wifi();
  // Calculate the PID values
  calculate_pid();

  // Display Kp, Ki, and PI values on separate lines of the OLED display
  displayMultipleFloats("Error", P, "PI", PI_value);
  if (error == 102)
  {
    handle_u_turn();
  }
  else if (error == 103)
  {
    if (random(0, 2) == 0)
    {
      turnLeft(180);
    }
    else
    {
      turnRight(180);
    }
    read_sensor_values();
  }
  else
  {
    calculate_pid();
    motor_control();
  }
  delay(500); // added so that it can make a return  journey
}
//}
