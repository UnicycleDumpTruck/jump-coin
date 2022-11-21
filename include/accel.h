// Jeff's reusable code for Adafruit's VS1053 Audio Featherwing
// Remember not to send RFM69 radio messages during audio plays

#ifndef accel_h
#define accel_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS3DH.h>

void accelSetup();
bool checkForJumps();

#endif