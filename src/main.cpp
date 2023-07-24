#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <U8g2lib.h> // Include the U8g2 library

const char *ssid = "Jhelum.net [Luqman House]";
const char *password = "7861234786";

WiFiServer server(80);

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

String data = "";
WiFiClient client;

// OLED display object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup()
{
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, freq, resolution);
  ledcSetup(channel_l2, freq, resolution);
  ledcSetup(channel_r1, freq, resolution);
  ledcSetup(channel_r2, freq, resolution);

  // Attach the channels to the GPIOs
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
  server.begin();
  Serial.print("Server started on IP: ");
  Serial.println(WiFi.localIP());

  // Initialize the OLED display
  u8g2.begin();
  u8g2.enableUTF8Print(); // Enable UTF-8 character printing

  // Display a startup message on the OLED display
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf); // Choose a font
  u8g2.setCursor(0, 15);
  u8g2.print("Motors Starting...");
  u8g2.sendBuffer();
}

// Function to display the current command on the OLED display
void displayCommandOnOLED(String command)
{
  u8g2.clearBuffer(); // Clear the display buffer
  u8g2.setFont(u8g2_font_6x10_tf); // Choose a font
  u8g2.setCursor(0, 15); // Set cursor position
  u8g2.print("Command: "); // Display text
  u8g2.print(command); // Display the current command
  u8g2.sendBuffer(); // Send the buffer to the OLED display
}

// Function to handle the received data
void handleData(String data)
{
  Serial.println("Received data: " + data);
  // Process the received data here if needed
}

// Function to set the motors to move forward
void moveForward(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, speed);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, speed);
  delay(20);
}

// Function to set the motors to move backward
void moveBackward(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, speed);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, speed);
  delay(20);
}

// Function to set the motors to turn right
void turnRight(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, 0);
}

// Function to set the motors to turn left
void turnLeft(int speed)
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, speed);
  ledcWrite(channel_l2, 0);
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
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, speed);
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

  // Display the received command on the OLED display
  displayCommandOnOLED(data);

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
  else if (data == "up")
  {
    speedUp();
  }
  else if (data == "down")
  {
    speedDown();
  }
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

void loop()
{
  // Handle client connections
  client = server.available();
  if (!client)
    return;

  data = checkClient();
  // Process the received data
  processData(data);
  handleData(data);
}
