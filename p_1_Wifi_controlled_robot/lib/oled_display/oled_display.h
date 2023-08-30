#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;
extern String request;

void drawRightArrow();
void drawLeftArrow();
void drawForwardArrow();
void drawBackwardArrow();
void drawStopCircle();

#endif
