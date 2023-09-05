#ifndef IR_SENSOR_PROCESSING_H
#define IR_SENSOR_PROCESSING_H

#define ir1 35
#define ir2 32
#define ir3 33
#define ir4 25
#define ir5 26

void setupSensors();
void readSensors(int sensorData[5]);
void printSensorData(int sensorData[5]);
int calculateError(int sensorData[5]);
#endif
