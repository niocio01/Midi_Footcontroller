#include <Arduino.h>
#include <core_pins.h>
#include <kinetis.h>


 #include "display.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
    delay(2000);
    Serial.println("Serial Connection Established.");

    displaySetup();
}

void loop()
{
    
}