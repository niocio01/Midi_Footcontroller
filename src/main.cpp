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

    initSD();

    displaySetup();

    initInputs();

    midiSetup();

    Led::init();

    setUpdateFlag();
}

void loop()
{
    checkInputs();

    updateDisplay();

    midiUpdate();

    Led::Test();
}
