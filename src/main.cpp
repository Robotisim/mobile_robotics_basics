#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "AS5600.h"
#include "dead_Reckoning.h"
#include "wifi_data_processing.h"

void setup()
{
  setupMotors();
  Serial.begin(115200);
  Wire.begin();
  setupEncoder0();
  setupEncoder1();
  setupWiFi();
  delay(1000);
}

void loop()
{
  calculate_traveling();
  Serial.print("X: " );
  Serial.print(x);
  Serial.print(" | Y: ");
  Serial.print (y);
 client = server.available();
  if (!client)
    return;
    
// Send the current x and y positions over WiFi
  sendPositionOverWiFi(x, y);
  data = processClientRequest();
  Serial.println(data);
  processData(data);
  delay(300);
}

