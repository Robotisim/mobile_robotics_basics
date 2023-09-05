#include "oled_display.h"
#include <U8g2lib.h>

// OLED display object
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
void setupOLED()
{
    // Initialize the OLED display
    u8g2.begin();
    u8g2.enableUTF8Print(); // Enable UTF-8 character printing
}

void displayMultipleFloats(const char *label1, float value1, const char *label2, float value2)
{
    u8g2.clearBuffer();              // Clear the display buffer
    u8g2.setFont(u8g2_font_6x10_tf); // Choose a font

    // Set cursor position for each line
    int yPosition1 = 15;
    int yPosition2 = yPosition1 + 12;

    u8g2.setCursor(0, yPosition1);
    u8g2.print(label1);
    u8g2.print(": ");
    u8g2.print(value1, 2);

    u8g2.setCursor(0, yPosition2);
    u8g2.print(label2);
    u8g2.print(": ");
    u8g2.print(value2, 2);

    u8g2.sendBuffer(); // Send the buffer to the OLED display
}
