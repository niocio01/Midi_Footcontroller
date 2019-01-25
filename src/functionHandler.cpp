#include <Arduino.h>
#include "configEditor.h"
#include "display.h"
#include "config.h"
#include "myMidi.h"



void bankUpPressed(void)
{
    uint8_t bank = getBank();
    changeBank(bank + 1);
    setUpdateFlag();
}

void bankDownPressed(void)
{
    uint8_t bank = getBank();
    changeBank(bank - 1);
    setUpdateFlag();
}

void modePressed(void)
{
    
}

void backPressed(void)
{
    
}

void savePressed(void)
{
    
}

void selectPressed(void)
{
    
}

void footButtonPressed(uint8_t button)
{
    Function_Type_t function = getButtonFunction(button);
    uint8_t midiCC = getButtonMidiCC(button);

    Serial.print("Button Nr. ");
    Serial.print(button);
    Serial.println(" Pressed");
    Serial.print("Function: ");
    Serial.println(function);

    switch (function)
    {
        case Target_Track_Start_Stop:
        sendMidiCC (getButtonMidiCC(button), 127);
        delay(10);
        sendMidiCC (getButtonMidiCC(button), 0);
        Serial.println("Track Started/Stopped\n");
        break;

        case Target_Track_Inc:
        sendMidiCC (getButtonMidiCC(button), 127);
        delay(10);
        sendMidiCC (getButtonMidiCC(button), 0);
        Serial.println("Target Track Increased\n");
        break;

        case Target_Track_Dec:
        sendMidiCC (getButtonMidiCC(button), 127);
        delay(10);
        sendMidiCC (getButtonMidiCC(button), 0);
        Serial.println("Target Track Decreased\n");
        break;

        default:
        Serial.println("not Implemented Function called.\n");
    }
}


