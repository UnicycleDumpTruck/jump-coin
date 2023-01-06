#include <Arduino.h>
#include <Adafruit_SleepyDog.h>

// Project Includes
#include "Version.h"
#include <pinout.h>
#include <audio.h>
#include <radio.h>
#include <accel.h>


// ███████╗███████╗████████╗██╗   ██╗██████╗
// ██╔════╝██╔════╝╚══██╔══╝██║   ██║██╔══██╗
// ███████╗█████╗     ██║   ██║   ██║██████╔╝
// ╚════██║██╔══╝     ██║   ██║   ██║██╔═══╝
// ███████║███████╗   ██║   ╚██████╔╝██║
// ╚══════╝╚══════╝   ╚═╝    ╚═════╝ ╚═╝

void setup()
{
  Serial.begin(9600);
  // while (!Serial)
  // {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }
  Serial.printf("\nProject jump-coin version v%s, built %s\n", VERSION, BUILD_TIMESTAMP);
  Serial.println("Setup function commencing...");
  vsAudioSetup();
  delay(100);
  radioSetup();
  delay(100);
  accelSetup();

  // LED SETUP
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Relay SETUP
  pinMode(RELAY_PIN, OUTPUT);

  // Test Relay for LED strip at boot
  digitalWrite(RELAY_PIN, HIGH);
  // Test sound playing at boot
  startAudio();
  delay(2000);
  digitalWrite(RELAY_PIN, LOW);

  Watchdog.enable(4000);
  Serial.println("Setup Complete");
}

// ██╗      ██████╗  ██████╗ ██████╗
// ██║     ██╔═══██╗██╔═══██╗██╔══██╗
// ██║     ██║   ██║██║   ██║██████╔╝
// ██║     ██║   ██║██║   ██║██╔═══╝
// ███████╗╚██████╔╝╚██████╔╝██║
// ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝

void loop()
{

  if (checkForJumps()){
    digitalWrite(RELAY_PIN, HIGH);
    startAudio();
    delay(2500);
    // stopAudio();
    sendGoEvent(1);
    digitalWrite(RELAY_PIN, LOW);
  }

  Watchdog.reset();
}