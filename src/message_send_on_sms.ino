#include <WiFi.h>
#include <WiFiUdp.h>
#include <U8g2lib.h>

const char* ssid = "Jhelum.net [Luqman House]";
const char* password = "7861234786";
const int udpPort = 1234;
WiFiUDP udp;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP IP Address: ");
  Serial.println(WiFi.localIP());

  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Waiting messages...");
  u8g2.sendBuffer();

  udp.begin(udpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Received message:");

    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }

    u8g2.drawStr(0, 25, incomingPacket);
    u8g2.sendBuffer();
    Serial.println(incomingPacket);
  }
}
