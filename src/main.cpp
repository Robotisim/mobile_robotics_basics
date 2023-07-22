#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "WiFi.h"
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

const char *ssid = "Jhelum.net [Luqman House]";
const char *password = "7861234786";

WiFiServer wifiServer(80); // Renamed WiFiServer instance to wifiServer
WebServer webServer(80);   // Renamed WebServer instance to webServer
String webpage = "";

// Define pin connections & motor's states
#define ml_1 27
#define ml_2 14
#define mr_1 26
#define mr_2 25

// Define channels for LEDC functions
#define channel_l1 0
#define channel_l2 1
#define channel_r1 2
#define channel_r2 3

// Frequency for LEDC function
#define freq 5000

// Resolution for LEDC function
#define resolution 8

// Define a variable to hold the current speed
int currentSpeed = 0; // Initial speed (adjust as needed)



void setup()
{
  // Motor control setup
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  ledcSetup(channel_l1, freq, resolution);
  ledcSetup(channel_l2, freq, resolution);
  ledcSetup(channel_r1, freq, resolution);
  ledcSetup(channel_r2, freq, resolution);

  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);

  Serial.begin(115200);
  Serial.println("Motors Starting");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  // Start the server
  wifiServer.begin();
  Serial.print("Server started on IP: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  webServer.begin();
  Serial.print("Web server started on IP: ");
  Serial.println(WiFi.localIP());

  // Web server setup
  webpage += "<h1>Robot Control</h1>";
  webpage += "<p><a href=\"/forward\"><button>Forward</button></a></p>";
  webpage += "<p><a href=\"/backward\"><button>Backward</button></a></p>";
  webpage += "<p><a href=\"/left\"><button>Left</button></a></p>";
  webpage += "<p><a href=\"/right\"><button>Right</button></a></p>";
  webpage += "<p><a href=\"/stop\"><button>Stop</button></a></p>";
  webpage += "<p><a href=\"/speedup\"><button>Speed Up</button></a></p>";
  webpage += "<p><a href=\"/speeddown\"><button>Speed Down</button></a></p>";
}

// Function to set the motors to move forward
void moveForward(int speed)
{
  // Ramp from 0 to the desired speed forward
  for (int i = 0; i <= speed; i++)
  {
    ledcWrite(channel_l1, speed);
    ledcWrite(channel_r1, speed);
    ledcWrite(channel_l2, i);
    ledcWrite(channel_r2, i);
    delay(20);
  }
}

// Function to set the motors to move backward
void moveBackward(int speed)
{
  // Ramp from 0 to the desired speed backward
  for (int i = 0; i <= speed; i++)
  {
    ledcWrite(channel_l1, i);
    ledcWrite(channel_r1, i);
    ledcWrite(channel_l2, speed);
    ledcWrite(channel_r2, speed);
    delay(20);
  }
}

// Function to set the motors to turn right
void turnRight(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, speed);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}

// Function to set the motors to turn left
void turnLeft(int speed)
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, speed);
}

// Function to stop the motors
void stopMotors()
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}

// Function to update the motor speed
void updateMotorSpeed(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, speed);
}

// Function to speed up the motors by 30 RPM
void speedUp()
{
  currentSpeed += 30;
  if (currentSpeed > 255)
  {
    currentSpeed = 255; // Limit the speed to the maximum value (255)
  }
  updateMotorSpeed(currentSpeed);
}

// Function to speed down the motors by 30 RPM
void speedDown()
{
  currentSpeed -= 30;
  if (currentSpeed < 0)
  {
    currentSpeed = 0; // Limit the speed to the minimum value (0)
  }
  updateMotorSpeed(currentSpeed);
}

void processData(String data)
{
  // Convert the received data to lowercase for case-insensitive comparison
  data.toLowerCase();

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
    turnRight(currentSpeed); // Set the speed as needed (0 to 255)
  }
  else if (data == "left")
  {
    turnLeft(currentSpeed); // Set the speed as needed (0 to 255)
  }
  else if (data == "stop")
  {
    stopMotors();
  }
  else if (data == "speedup")
  {
    speedUp();
  }
  else if (data == "speeddown")
  {
    speedDown();
  }
}

void loop()
{
  // Handle client connections for WiFi server
  WiFiClient client = wifiServer.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        String data = client.readStringUntil('\n');
        // Process the received data
        processData(data);
        // Send a response (optional)
        client.println("Data received successfully!");
      }
    }
    // Close the connection
    client.stop();
  }

  // Handle client connections for Web server
  webServer.handleClient();

  delay(3000);
}