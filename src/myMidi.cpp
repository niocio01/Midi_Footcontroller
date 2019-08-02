#include <MIDI.h>
#include "configEditor.h"
#include "myMidi.h"
#include "functionHandler.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 1;

uint8_t midiClockCounter = 0;
uint8_t mesureCounter = 0;

midiCommand_t commandQueue[50];
bool sendQueuedCommands = false;


void addMidiCommandToQueue(uint8_t cc , uint8_t val)
{
    for (int i = 49 ; i >= 1 ; i--)
    {
        commandQueue[i] = commandQueue[i-1];
    }
    commandQueue[0].cc = cc;
    commandQueue[0].val = val;
}




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
        mesureCounter ++;
        if (mesureCounter == 4)
        {
            mesureCounter = 0;
            FunctionHandler::updateStatus();
        }
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

    for (int i = 0 ; i < 50 ; i++) // set all slots to "empty"
    {
        commandQueue[i].cc = NO_COMMAND;
    }
}

void midiUpdate(void)
{
    MIDI.read();

    if (sendQueuedCommands == true)
    {
        sendQueuedCommands = false;
        uint8_t channel = getMidiChannel(); // send all commands to the same channel

        for (int i = 49; i >= 0 ; i--)
        {
            if (commandQueue[i].cc != NO_COMMAND)
            {
                MIDI.sendControlChange(commandQueue[i].cc , commandQueue[i].val , channel );
                commandQueue[i].cc = NO_COMMAND; // reset current slot
                delay(15);
            }
        }
    }

}


