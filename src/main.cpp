#include <Arduino.h>
#include <Adafruit_SleepyDog.h>

// Project Includes
#include "Version.h"
#include <pinout.h>
#include <audio.h>
#include <radio.h>
#include <accel.h>

// Used in detecting repeat/"stuck" accelerometer click sense
#define MINTIMEBETWEENJUMPS 4000
long timeLastJump = 0;


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
  radioSetup();
  delay(100);
  vsAudioSetup();
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
    // If we're getting repeating triggers, reset accelerometer
    if ((millis() - timeLastJump) < MINTIMEBETWEENJUMPS) {
      Serial.println("Resetting accelerometer...");
      accelSetup();
    }
    timeLastJump = millis();
    // Light the LED ring
    digitalWrite(RELAY_PIN, HIGH);
    // Play the chaching sound
    startAudio();
    // Wait fo the audio to stop, radio can't send during play
    delay(2500);
    // stopAudio();
    sendGoEvent(1);
    // Turn off the LED ring
    digitalWrite(RELAY_PIN, LOW);
  }

  Watchdog.reset();
}