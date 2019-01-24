#include <Arduino.h>
#include <core_pins.h>
#include <kinetis.h>

#include <MIDI.h>

#include "display.h"
#include "inputs.h"
#include "TimedTasks.h"
#include "myMidi.h"
#include "led.h"
#include "mySD.h"
#include "i2c_mux.h"

int count = 0;
uint32_t lastButtons = 0;

void setup()
{
    // pinMode(LED_BUILTIN, OUTPUT);

    //pinMode(4, INPUT);

  //  Serial.begin(115200);
  //  delay(2000);
  //  Serial.println("Serial Connection Established.");

    initSD();

    displaySetup();

    initInputs();

    //midiSetup();

    //initLed();

    

    // sdWriteTest();
}



void loop()
{
    checkInputs();

    updateDisplay();

    
    //delay(2000);

    // Serial.print(FTM3_CNT);
    // Serial.print("     ");
    // Serial.println(FTM3_C0V);
    //Serial.println(getInputs(),BIN);
    //Serial.println(digitalRead(4),BIN);



  //  if ( lastButtons != getInputs())
  //  {
  //      printInputs(getInputs());
  //  }
  //  lastButtons = getInputs();
    //delay(2000);

    //midiInputTest ();

    //midiOutputTest();

    //ledTest();
}
