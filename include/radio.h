#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>

#include <pinout.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>

#define MY_ADDRESS 53 // Pennies 50, 51; Nickel: 52; Dime: 53;
#define RF69_FREQ 915.0

void radioSetup();
void sendGoEvent(uint8_t s);

#endif