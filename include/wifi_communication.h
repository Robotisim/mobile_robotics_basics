#ifndef WIFI_COMMUNICATION_H
#define WIFI_COMMUNICATION_H

#include <Arduino.h>
#include <WiFi.h>

extern WiFiClient client;
extern String data;
extern WiFiServer server; // Declare the WiFiServer instance

void setupWiFi();
String checkClient(void);
void handleData(String data);

#endif
