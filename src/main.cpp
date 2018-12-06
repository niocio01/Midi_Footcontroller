#include <Arduino.h>
#include <core_pins.h>
#include <kinetis.h>


 #include "display.h"
 #include "inputs.h"
 #include  "TimedTasks.h"


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    delay(2000);
    Serial.println("Serial Connection Established.");

    displaySetup();

    initTimedTasks();
}

void loop()
{
    delay(2000);

    Serial.print(FTM3_CNT);
    Serial.print("     ");
    Serial.println(FTM3_C0V);
   // Serial.println(getInputs());
}