#ifndef ADAFRUIT_SETUP_H
#define ADAFRUIT_SETUP_H
#include <Adafruit_MPU6050.h>
#include <Wire.h>

void AdafruitSetup(Adafruit_MPU6050 &mpu);
void scan_mpu();

#endif