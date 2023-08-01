#ifndef WIFI_UDP_H
#define WIFI_UDP_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

extern char packet[8];
extern char packetBuffer[255];

void connectToWifi();
void send_sensor_values_over_wifi();
void parseUdpMessage();

#endif // WIFI_UDP_H
