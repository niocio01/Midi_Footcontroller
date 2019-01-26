#include <Arduino.h>
#include "configEditor.h"
#include "display.h"
#include "config.h"
#include "myMidi.h"

uint8_t currentTargetTrack = 0;
bool trackPlaying[5] = {false};
bool trackRecording[5] = {false};

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

    if ((function >= Select_Track_Play_Rec) && (function <= Select_Track_Play_Level))
    {
        uint8_t targetTrack = getButtonAddPar1(button);

        int8_t difference = targetTrack - currentTargetTrack;

        currentTargetTrack = targetTrack;

        if (difference == -4 or difference == 1)
        {
            sendMidiCC(getTargetTrackCC(Inc), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Inc), 0);
        }

        else if (difference == -3 or difference == 2)
        {
            sendMidiCC(getTargetTrackCC(Inc), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Inc), 0);
            delay(10);
            sendMidiCC(getTargetTrackCC(Inc), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Inc), 0);
        }

        else if (difference == -2 or difference == 3)
        {
            sendMidiCC(getTargetTrackCC(Dec), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Dec), 0);
            delay(10);
            sendMidiCC(getTargetTrackCC(Dec), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Dec), 0);
        }

        else if (difference == -1 or difference == 4)
        {
            sendMidiCC(getTargetTrackCC(Dec), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Dec), 0);
        }

        switch (function)
        {
        case Select_Track_Play_Rec:
            sendMidiCC(getTargetTrackCC(Play_Rec), 127);
            delay(10);
            sendMidiCC(getTargetTrackCC(Play_Rec), 0);

            if (trackRecording[currentTargetTrack] == true)
            {
                trackRecording[currentTargetTrack] = false;
            }

            trackPlaying[currentTargetTrack] = true;
            break;

        case Select_Track_Start_Stop:

            if (trackPlaying[currentTargetTrack] == true) // if its playing, Stop it
            {
                trackPlaying[currentTargetTrack] = false;
                trackRecording[currentTargetTrack] = false;

                sendMidiCC(getTargetTrackCC(Stop), 127);
                delay(10);
                sendMidiCC(getTargetTrackCC(Stop), 0);
            }
            else // if its stopped, start it again
            {
                trackPlaying[currentTargetTrack] = true;
                trackRecording[currentTargetTrack] = false; // maybe The looper remembers

                sendMidiCC(getTargetTrackCC(Play_Rec), 127);
                delay(10);
                sendMidiCC(getTargetTrackCC(Play_Rec), 0);
            }
            break;

        default:
            break;
        }
    }

    else
    {
        switch (function)
        {
        case Target_Track_Inc:
            sendMidiCC(getButtonMidiCC(button), 127);
            delay(10);
            sendMidiCC(getButtonMidiCC(button), 0);
            Serial.println("Target Track Increased\n");
            break;

        case Target_Track_Dec:
            sendMidiCC(getButtonMidiCC(button), 127);
            delay(10);
            sendMidiCC(getButtonMidiCC(button), 0);
            Serial.println("Target Track Decreased\n");
            break;

        case Target_Track_Play_Rec:
            sendMidiCC(getButtonMidiCC(button), 127);
            delay(10);
            sendMidiCC(getButtonMidiCC(button), 0);
            Serial.println("Track Started/Stopped\n");
            break;

        default:
            Serial.println("not Implemented Function called.\n");
        }
    }
}
