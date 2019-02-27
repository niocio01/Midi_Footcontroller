#include <MIDI.h>
#include "configEditor.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 1;

uint8_t midiClockCounter = 0;


void handleStart(void) // callback function
{
    midiClockCounter = 0;
    Serial.println("Midi Clock Start");
}

void handleClock(void) // callback function
{
    midiClockCounter ++;

    if (midiClockCounter == 24)
    {
        midiClockCounter = 0;
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
}

void sendMidiCC(uint8_t cc, uint8_t val)
{
    MIDI.sendControlChange(cc, val, getMidiChannel() );
}

void midiSetup(void)
{
    MIDI.setHandleStart(handleStart); // enable Midi Callback for start messages

    MIDI.setHandleClock(handleClock); // enable Midi Callback for Clock messages

    MIDI.begin();

    pinMode(LED_BUILTIN, OUTPUT); // Debug LED
}

void midiUpdate(void)
{
    MIDI.read();
}
