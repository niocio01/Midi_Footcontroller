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
#include "lightController.h"

int count = 0;
uint32_t lastButtons = 0;

void setup()
{

    initSD();
    
    Led::init();

    ButtonLights::init();
// 
    // ButtonLights::setTrackState(0, ButtonLights::EMPTY);
    // ButtonLights::setTrackState(1, ButtonLights::EMPTY);
    // ButtonLights::setTrackState(2, ButtonLights::EMPTY);
// 
    // ButtonLights::update();

    // displaySetup();

    TimedTasks::timerInit();

    inputs::initInputs();

    // midiSetup();

   

    // setUpdateFlag();

    // Led::setMasterBrightness(100);

    

  
     // Led::Segment TrackOne_Play(0, 8);
     // Led::Segment TrackOne_OVD(8, 16);
     // Led::Segment SpecialOne(8*4, 8*5);
     // 
     // Led::Segment TrackTwo_Play(8*2, 8*3);
     // Led::Segment TrackTwo_OVD(8*3, 8*4);
     // Led::Segment SpecialTwo(8*5, 8*6);
//// 
     // TrackOne_Play.setAll(255, 0, 0, 0);
     // TrackOne_OVD.setAll(0, 255, 0, 0);
     // TrackTwo_Play.setAll(0, 0, 255, 0);
     // TrackTwo_OVD.setAll(0, 0, 0, 255);
     // SpecialOne.setAll(RGBW_ORANGE);
     // SpecialTwo.setAll(RGBW_YELLOW);

    //ButtonLights::Track1_Play.setAll(255,0,0,0);

    // Led::update();

    

    Serial.println("Setup done");
}

void loop()
{
    inputs::checkInputs();
// 
    // uint32_t inputs = inputs::getInputs();
    // inputs::printInputs(inputs);
    // delay(1000);

    // updateDisplay();

    // midiUpdate();

    //Led::update();
    
    // Led::Test();

    // Serial.print("1");
}
