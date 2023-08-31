#include "wifi_data_processing.h"
WiFiClient client;
WiFiServer server(80);
const char *ssid = "Jhelum.net [Luqman House]";
const char *password = "7861234786";
String request;

void setupWiFi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print("Connecting to AP...");
    }
    server.begin();
    Serial.print("Connected to WiFi with IP: ");
    Serial.println(WiFi.localIP());
}

void processClientRequest()
{
    client = server.available();
    if (!client)
        return;

    while (!client.available())
    {
        delay(1);
    }

    request = client.readStringUntil('\r');
    request.remove(0, 5);
    request.remove(request.length() - 9, 9);

    }