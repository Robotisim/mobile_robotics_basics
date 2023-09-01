#include "wifi_data_processing.h"
#include <ESPAsyncWebServer.h>
WiFiClient client;
WiFiServer server(80);
const char *ssid = "Jhelum.net [Luqman House]";
const char *password = "7861234786";
String data = "";

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

String processClientRequest(void)
{
    while (!client.available())
    {
        delay(1);
    }

    String request = client.readStringUntil('\r');
    request.remove(0, 5);
    request.remove(request.length() - 9, 9);

    return request;
}

void processCoordinates(float x, float y)
{
    // Process the received x and y coordinates
    // Replace this with the actual code to handle the coordinates

    // For example, you can print the coordinates to the Serial Monitor
    Serial.print("Received Coordinates - X: ");
    Serial.print(x);
    Serial.print(" | Y: ");
    Serial.println(y);

    // You can also perform any other actions or calculations based on the coordinates
    // For instance, controlling motors, performing calculations, etc.
}

void sendPositionOverWiFi(float x, float y)
{
    if (client.connect(WiFi.localIP(), 80))
    {
    Serial.println("Connected to server");

    // Create a JSON string to send
    String dataToSend = String(x) + ","+ String(y);
    
    // Send a POST request to the server
    client.println("POST /data HTTP/1.1");
    client.println("Host: " + String(WiFi.localIP()));
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(dataToSend.length());
    client.println();
    client.println(dataToSend);
    
    Serial.println("Data sent to server" + dataToSend);
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }
}