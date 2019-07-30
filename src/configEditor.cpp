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

Led::Colors_t getTrackColor (uint8_t track)
{
    return config.settings.TrackColor[track];
}


uint8_t getButtonMidiCC(uint8_t button)
{
    return config.settings.function[button].midi_CC;
}



uint8_t getStartOnStart(uint8_t track)
{
    return config.settings.StartOnStart[track];
}
uint8_t getStopOnStart(uint8_t track)
{
    return config.settings.StopOnStart[track];
}
uint8_t getStopOnStop(uint8_t track)
{
    return config.settings.StopOnStop[track];
}
uint8_t getStartOnStop(uint8_t track)
{
    return config.settings.StartOnStop[track];
}



Function_Type_t getButtonFunction(uint8_t button)
{
    return config.settings.function[button].function;
}

uint8_t getTargetTrackCC(TargetTrackCC_Type_t type)
{
    return config.settings.TargetTrackCC[type];
}


uint8_t getButtonAddPar1(uint8_t button)
{
    return config.settings.function[button].additionalParameter[0];
}

uint8_t getButtonAddPar2(uint8_t button)
{
    return config.settings.function[button].additionalParameter[1];
}
