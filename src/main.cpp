#include <Arduino.h>
#include <core_pins.h>
#include <kinetis.h>


 #include "display.h"
 #include "inputs.h"


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(9600);
    delay(2000);
    Serial.println("Serial Connection Established.");

    displaySetup();

    initInputs();
}

void loop()
{
    delay(2000);

    Serial.print(FTM1_CNT);
    Serial.print("     ");
    Serial.println(FTM1_C0V);
   // Serial.println(getInputs());
}