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

    Led::setMasterBrightness(255);

    Led::Segment firstFive(0, 5, 10);

    firstFive.setLed(0, 255, 0, 0, 0);
    firstFive.setLed(1, 0, 255, 0, 0);
    firstFive.setLed(2, 0, 0, 255, 0);
    firstFive.setLed(3, 0, 0, 100, 0);

   // firstFive.setAll(0, 255, 0, 0);

    Led::Segment secondFive(5, 10, 50);

    secondFive.setAll(RGBW_ORANGE);

    Led::update();
}

void loop()
{
    checkInputs();

    updateDisplay();

    midiUpdate();

    // Led::Test();
}
