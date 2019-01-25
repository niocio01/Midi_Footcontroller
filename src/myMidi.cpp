#include <MIDI.h>
#include "configEditor.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 1;

void midiSetup(void)
{
    MIDI.begin();
}

void midiInputTest(void)
{

    int type, note, velocity, channel, d1, d2;

    long time = millis();

    if (MIDI.read())
    { // Is there a MIDI message incoming ?
        byte type = MIDI.getType();
        switch (type)
        {
        case midi::NoteOn:
            note = MIDI.getData1();
            velocity = MIDI.getData2();
            channel = MIDI.getChannel();
            if (velocity > 0)
            {
                Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
            }
            else
            {
                Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
            }
            break;
        case midi::NoteOff:
            note = MIDI.getData1();
            velocity = MIDI.getData2();
            channel = MIDI.getChannel();
            Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
            break;
        default:
            d1 = MIDI.getData1();
            d2 = MIDI.getData2();
            Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
        }
    }
    if (millis() - time > 10000)
    {
        time += 10000;
        Serial.println("(inactivity)");
    }
}

void midiOutputTest(void)
{
    MIDI.sendControlChange(2, 127, channel);
    delay(3000);
    MIDI.sendControlChange(2, 0, channel);
    delay(3000);
}

void sendMidiCC(uint8_t cc, uint8_t val)
{
    MIDI.sendControlChange(cc, val, getMidiChannel() );
}