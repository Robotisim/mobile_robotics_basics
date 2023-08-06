#include "wifi_communication.h"
#include <WiFi.h>

const char *ssid = "Jhelum.net [Luqman House]";
const char *password = "7861234786";
WiFiServer server(80);
WiFiClient client;
String data = "";



void setupWiFi()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  // Start the server
  server.begin();
  Serial.print("Server started on IP: ");
  Serial.println(WiFi.localIP());
}

String checkClient(void)
{
  while (!client.available())
    delay(1);

  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);

  return request;
}

// Function to handle the received data
void handleData(String data)
{
  Serial.println("Received data: " + data);
  // Process the received data here if needed
}
