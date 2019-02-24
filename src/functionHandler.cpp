#include <Arduino.h>
#include "configEditor.h"
#include "display.h"
#include "config.h"
#include "myMidi.h"

uint8_t currentTargetTrack = 1;
bool trackPlaying[5] = {false};
bool trackRecording[5] = {false};
bool TrackHasRecording[5] = {false};

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

void goToTargetTrack(uint8_t targetTrack)
{
    int8_t difference = targetTrack - currentTargetTrack;

    currentTargetTrack = targetTrack;

    if (difference != 0)
    {
        if (difference == -4 or difference == 1)
        {
            sendMidiCC(getTargetTrackCC(Inc), 127);
            delay(15);
            sendMidiCC(getTargetTrackCC(Inc), 0);
        }

        else if (difference == -3 or difference == 2)
        {
            sendMidiCC(getTargetTrackCC(Inc), 127);
            delay(15);
            sendMidiCC(getTargetTrackCC(Inc), 0);
            delay(15);
            sendMidiCC(getTargetTrackCC(Inc), 127);
            delay(15);
            sendMidiCC(getTargetTrackCC(Inc), 0);
        }

        else if (difference == -2 or difference == 3)
        {
            sendMidiCC(getTargetTrackCC(Dec), 127);
            delay(15);
            sendMidiCC(getTargetTrackCC(Dec), 0);
            delay(15);
            sendMidiCC(getTargetTrackCC(Dec), 127);
            delay(15);
            sendMidiCC(getTargetTrackCC(Dec), 0);
        }

        else if (difference == -1 or difference == 4)
        {
            sendMidiCC(getTargetTrackCC(Dec), 127);
            delay(15);
            sendMidiCC(getTargetTrackCC(Dec), 0);
        }
        delay(15);
    }
}

void startTrack(uint8_t track)
{
    goToTargetTrack(track);
    sendMidiCC(getTargetTrackCC(Play_Rec), 127);
    delay(15);
    sendMidiCC(getTargetTrackCC(Play_Rec), 0);
    trackPlaying[track - 1] = true;
    TrackHasRecording[track - 1] = true;
    Serial.print("Track Nr ");
    Serial.print(track);
    Serial.println(" Started");
}

void stopTrack(uint8_t track)
{
    goToTargetTrack(track);
    sendMidiCC(getTargetTrackCC(Stop), 127);
    delay(15);
    sendMidiCC(getTargetTrackCC(Stop), 0);
    trackPlaying[track - 1] = false;
    Serial.print("Track Nr ");
    Serial.print(track);
    Serial.println(" Stopped");
}

void startOnStart(uint8_t track, bool startWithOverdub)
{
    uint8_t TracksToStart = getStartOnStart(track - 1);

    if (TracksToStart & ((int)pow(2, track - 1))) // is the pressed Track supposed to be started
    {
        startTrack(track);
        if (((startWithOverdub == true) & (TrackHasRecording[track - 1] == true))) // press it twice to go into overdub if its allready recorded
        {
            startTrack(track); // can also be used to start overdub.
            delay(15);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (((TrackHasRecording[i] == true) & (trackPlaying[i] == false)))
        {
            if ((TracksToStart & ((int)pow(2, i))) && (i != track - 1)) // is the this Track supposed to be started and isnt the pressed one
            {
                startTrack(i + 1);
                delay(15);
            }
        }
    }
}

void stopOnStart(uint8_t track)
{
    uint8_t TracksToStop = getStopOnStart(track - 1);

    if (TracksToStop & ((int)pow(2, track - 1))) // is the pressed Track supposed to be started
    {
        stopTrack(track);
        delay(15);
    }

    for (int i = 0; i < 5; i++)
    {
        if (((TrackHasRecording[i] == true) & (trackPlaying[i] == true)))
        {
            if ((TracksToStop & ((int)pow(2, i))) && (i != track - 1)) // is the this Track supposed to be started and isnt the pressed one
            {
                stopTrack(i + 1);
                delay(15);
            }
        }
    }
}

void stopOnStop(uint8_t track)
{
    uint8_t TracksToStop = getStopOnStop(track - 1);

    if (TracksToStop & ((int)pow(2, track - 1))) // is the pressed Track supposed to be started
    {
        stopTrack(track);
    }

    for (int i = 0; i < 5; i++)
    {
        if ((TracksToStop & ((int)pow(2, i))) && (trackPlaying[i] == true) && (i != track - 1))
        {
            stopTrack(i + 1);
            delay(15);
        }
    }
}

void footButtonPressed(uint8_t button)
{
    Function_Type_t function = getButtonFunction(button);
    uint8_t track = getButtonAddPar1(button);
    // uint8_t midiCC = getButtonMidiCC(button);

    Serial.print("Button Nr. ");
    Serial.print(button);
    Serial.println(" Pressed");
    Serial.print("Function: ");
    Serial.println(function);

    if ((function >= Select_Track_Play_Rec) && (function <= Select_Track_Play_Level))
    {

        switch (function)
        {
        case Select_Track_Start_Stop:
            if (trackPlaying[track - 1] == false) // start track
            {
                stopOnStart(track); // stop first, to allow start from the begining
                delay(15);
                startOnStart(track, false); // start track
            }
            else // stop
            {
                stopOnStop(track);
            }

            break;

        case Select_Track_Play_Rec: // overdub

            if ((trackPlaying[track - 1] == true) || (TrackHasRecording[track - 1] == false)) // start Track
            {
                startTrack(track); // also does Overdub on/off
            }
            else // Start twise to enable Overdub
            {
                startTrack(track);
                delay(15);
                startTrack(track); // also does Overdub on/off
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
            delay(15);
            sendMidiCC(getButtonMidiCC(button), 0);
            Serial.println("Target Track Increased\n");
            break;

        case Target_Track_Dec:
            sendMidiCC(getButtonMidiCC(button), 127);
            delay(15);
            sendMidiCC(getButtonMidiCC(button), 0);
            Serial.println("Target Track Decreased\n");
            break;

        case Target_Track_Play_Rec:
            sendMidiCC(getButtonMidiCC(button), 127);
            delay(15);
            sendMidiCC(getButtonMidiCC(button), 0);
            Serial.println("Track Started/Stopped\n");
            break;

        default:
            Serial.println("not Implemented Function called.\n");
        }
    }
}
