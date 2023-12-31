#include "oled_display.h"



void drawRightArrow() {

    for (int i = -1; i <= 1; i++) {
      display.drawLine(30, 15 + i, 80, 15 + i, WHITE);
    }
    // Upper diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(80, 15, 60 + i, 10 + j, WHITE);
      }
    }
    // Lower diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(80, 15, 60 + i, 20 + j, WHITE);
      }
    }
  }
void drawLeftArrow() {
    for (int i = -1; i <= 1; i++) {
      display.drawLine(80, 15 + i, 30, 15 + i, WHITE);
    }
    // Upper diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(30, 15, 50 + i, 10 + j, WHITE);
      }
    }
    // Lower diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(30, 15, 50 + i, 20 + j, WHITE);
      }
    }
  }
  void drawForwardArrow() {
    // up
    for (int i = -1; i <= 1; i++) {
      display.drawLine(55 + i, 5, 55 + i, 25, WHITE);
    }
    // Left diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(45, 15, 55 + i, 5 + j, WHITE);
      }
    }
    // Right diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(65, 15, 55 + i, 5 + j, WHITE);
      }
    }
  }
  void drawBackwardArrow() {

    // Vertical line
    for (int i = -1; i <= 1; i++) {
      display.drawLine(55 + i, 5, 55 + i, 20, WHITE);
    }
    // Left diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(45, 15, 55 + i, 20 + j, WHITE);
      }
    }
    // Right diagonal
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        display.drawLine(65, 15, 55 + i, 20 + j, WHITE);
      }
    }
  }
  void drawStopCircle() {
    for (int i = -1; i <= 1; i++) {
      display.drawCircle(64, 15, 10 + i, WHITE);
    }
  }
