#include "ir_sensor_processing.h"
#include <Arduino.h>

void setupSensors() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void readSensors(int sensorData[5]) {
  sensorData[0] = !digitalRead(ir1);
  sensorData[1] = !digitalRead(ir2);
  sensorData[2] = !digitalRead(ir3);
  sensorData[3] = !digitalRead(ir4);
  sensorData[4] = !digitalRead(ir5);
}

void printSensorData(int sensorData[5]) {
  Serial.print(sensorData[0]);
  Serial.print(",");
  Serial.print(sensorData[1]);
  Serial.print(",");
  Serial.print(sensorData[2]);
  Serial.print(",");
  Serial.print(sensorData[3]);
  Serial.print(",");
  Serial.println(sensorData[4]);
}

int calculateError(int sensorData[5]){
  int error =0;
  int sensorValue =0;

  for(int i=0;i<5;i++){
    sensorValue|=(sensorData[i]<<i);

  }

  switch (sensorValue) {
    case 0b11110: error = -6; break;
    case 0b11100: error = -5; break;
    case 0b10000: error = -4; break;
    case 0b11000: error = -3; break;
    case 0b01000: error = -2; break;
    case 0b01100: error = -1; break;
    case 0b00100: error =  0; break;
    case 0b00110: error =  1; break;
    case 0b00010: error =  2; break;
    case 0b00011: error =  3; break;
    case 0b00001: error =  4; break;
    case 0b00111: error =  5; break;
    case 0b01111: error =  6; break;
    case 0b00000: error = 102; break;
    case 0b11111: error = 0; break;
    default: error = 103;
  }
  return error;


}