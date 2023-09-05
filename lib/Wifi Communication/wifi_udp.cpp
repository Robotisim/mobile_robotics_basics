#include <Arduino.h>
#include "wifi_udp.h"
#include "motor_control.h"
#include "pi_controller.h"

const char *ssid = "Jhelum.net [Luqman House]";
const char *password = "7861234786";
const char *serverAddress = "192.168.100.9"; // Replace with your server IP or domain
const int serverPort = 8888;

WiFiUDP udp;

char packet[8];
char packetBuffer[255];

void connectToWifi()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nConnected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(3000);
  udp.begin(8888);
}

void send_sensor_values_over_wifi()
{
  // char packet[20]; // Increase the buffer size to accommodate three sensor values

  udp.beginPacket(serverAddress, serverPort);

  // Convert and send the first sensor value
  dtostrf(sensor[0], 5, 2, packet);
  udp.write(packet[0]); // uint8_t
  udp.write(packet[1]);
  udp.write(packet[2]);
  udp.write(packet[3]);
  udp.write(packet[4]);
  udp.write(' '); // Add a space as a delimiter

  // Convert and send the second sensor value
  dtostrf(sensor[1], 5, 2, packet);
  udp.write(packet[0]); // uint8_t
  udp.write(packet[1]);
  udp.write(packet[2]);
  udp.write(packet[3]);
  udp.write(packet[4]);
  udp.write(' ');

  // Convert and send the third sensor value
  dtostrf(sensor[2], 5, 2, packet);
  udp.write(packet[0]); // uint8_t
  udp.write(packet[1]);
  udp.write(packet[2]);
  udp.write(packet[3]);
  udp.write(packet[4]);

  dtostrf(sensor[3], 5, 2, packet);
  udp.write(packet[0]); // uint8_t
  udp.write(packet[1]);
  udp.write(packet[2]);
  udp.write(packet[3]);
  udp.write(packet[4]);

  dtostrf(sensor[4], 5, 2, packet);
  udp.write(packet[0]); // uint8_t
  udp.write(packet[1]);
  udp.write(packet[2]);
  udp.write(packet[3]);
  udp.write(packet[4]);

  udp.endPacket();

  Serial.print(sensor[0]);
  Serial.print(" / ");
  Serial.print(sensor[1]);
  Serial.print(" / ");
  Serial.print(sensor[2]);
  Serial.print(" / ");
  Serial.print(sensor[3]);
  Serial.print(" / ");
  Serial.println(sensor[4]);
}


// here we recieve the upd message and process is
void parseUdpMessage()
{

  // Read sensor data
  int sensorValue0;
  int sensorValue1;
  int sensorValue2;
  int sensorValue3;
  int sensorValue4;
  udp.read(packetBuffer, 255);
  stopMotors();
  char *strtokIndx;
  strtokIndx = strtok(packetBuffer, ",");
  sensorValue0 = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  sensorValue1 = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  sensorValue2 = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  sensorValue3 = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  sensorValue4 = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  Right_motor_speed = atoi(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  Left_motor_speed = atoi(strtokIndx);

  Serial.print("\n\n\nSensor0 / Sensor1 / Sensor2 / Sensor3 / Sensor4 =");
  Serial.print(sensorValue0);
  Serial.print("/");
  Serial.print(sensorValue1);
  Serial.print("/");
  Serial.print(sensorValue2);
  Serial.print("/");
  Serial.print(sensorValue3);
  Serial.print("/");
  Serial.print(sensorValue4);
  Serial.print("M_R / M_L ");
  Serial.print(Left_motor_speed);
  Serial.print(" // ");
  Serial.print(Right_motor_speed);
  Serial.println("\n\n\nGET Ready !!");

  // No need for the delay here
  delay(1000);
  start_robot();
}
