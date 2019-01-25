#include <Arduino.h>
#include "config.h"
#include "inputs.h"

extern config_t config;

uint8_t getBank (void)
{
    return config.globalSettings.currentBank;
}

uint8_t getMidiChannel (void)
{
    return config.globalSettings.midiChannel;
}

void changeBank(uint8_t newBank)
{
    if (newBank > 0 and newBank < 100)
    {
        writeBank(config.globalSettings.currentBank);
        config.globalSettings.currentBank = newBank;
        readBank(newBank);
    }
}


uint8_t getButtonMidiCC(uint8_t button)
{
    return config.settings.function[button].midi_CC;
}

Function_Type_t getButtonFunction(uint8_t button)
{
    return config.settings.function[button].function;
}

