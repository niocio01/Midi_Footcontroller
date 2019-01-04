#include <Arduino.h>
#include <core_pins.h>
#include <kinetis.h>

#include <MIDI.h>


 #include "display.h"
 #include "inputs.h"
 #include  "TimedTasks.h"
 #include "myMidi.h"


void setup()
{
   // pinMode(LED_BUILTIN, OUTPUT);

   //pinMode(4, INPUT);

    Serial.begin(115200);
    delay(2000);
    Serial.println("Serial Connection Established.");

    displaySetup();

    //initInputs();

    //initTimedTasks();

    midiSetup();

    
}

void loop()
{
    //delay(2000);

   // Serial.print(FTM3_CNT);
   // Serial.print("     ");
   // Serial.println(FTM3_C0V);
    //Serial.println(getInputs(),BIN);
    //Serial.println(digitalRead(4),BIN);

    static uint32_t lastInput = 0;

    

  //  if (getInputs() != lastInput)
  //  {
  //      if(getInputs() != 0)
  //      {
  //          printInputs(getInputs());
  //      }    
  //  lastInput = getInputs();
  //  }


  //midiInputTest ();

  
 midiOutputTest();


}

