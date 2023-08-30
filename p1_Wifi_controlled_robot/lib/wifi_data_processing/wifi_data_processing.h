#ifndef WIFI_DATA_H
#define WIFI_DATA_H

#include <WiFi.h>

// Global Variables
extern WiFiClient client;
extern WiFiServer server;
extern const char *ssid;
extern const char *password;
extern String request;

void setupWiFi();
void processClientRequest();

#endif
