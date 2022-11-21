#include <Arduino.h>
#include <accel.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();    
    
// Adjust this number for the sensitivity of the 'click' force    
// this strongly depend on the range! for 16G, try 5-10    
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80    
#define CLICKTHRESHHOLD 60 // Higher numbers are less senstive    

void accelSetup(){
    if (!lis.begin(0x18)) { // change this to 0x19 for alternative i2c address
        delay(2000);
        Serial.println("Couldnt start LIS3DH!!!");
        // while (1);
    } else {
        Serial.println("LIS3DH found!");
    }

    lis.setRange(LIS3DH_RANGE_8_G); // 2, 4, 8 or 16 G!

    Serial.print("Range = ");
    Serial.print(2 << lis.getRange());
    Serial.println("G");

    // 0 = turn off click detection & interrupt
    // 1 = single click only interrupt output
    // 2 = double click only interrupt output, detect single click
    // Adjust threshhold, higher numbers are less sensitive
    lis.setClick(1, CLICKTHRESHHOLD);
    delay(100); 
}

bool checkForJumps(){

uint8_t click = lis.getClick();
    if (click == 0) {
        return false;
    }
    if (!(click & 0x30)){
        return false;
    }
    Serial.print("Click detected (0x");
    Serial.print(click, HEX);
    Serial.print("): ");
    if (click & 0x10)
    {
        Serial.println(" single click, returning true");
        return true;
    }
    return false;
}
