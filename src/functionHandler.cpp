#include <Arduino.h>
#include "configEditor.h"
#include "display.h"
#include "config.h"
#include "myMidi.h"
#include "lightController.h"
#include "functionHandler.h"

namespace FunctionHandler
{

uint8_t currentTargetTrack = 1;

trackState_t trackState[5] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
trackState_t oldTrackState[5] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};

bool waitForNextMesure = true;

// bool trackPlaying[5] = {false};
// bool trackRecording[5] = {false};
// bool trackHasRecording[5] = {false};

void footButtonPressed(uint8_t button)
{
    Function_Type_t function = getButtonFunction(button);
    uint8_t track = getButtonAddPar1(button);
    // uint8_t midiCC = getButtonMidiCC(button);

    Serial.print("Button Nr. ");
    Serial.print(button);
    Serial.print(" Pressed    ");
    Serial.print(" Track");
    Serial.print(track);
    Serial.print("    Function: ");
    // Serial.println(function);

    switch (function)
    {
    case Select_Track_Start_Stop:
        Serial.println("Track Start/Stop");
        switch (trackState[track])
        {
        case EMPTY:
        Serial.print("Empty");
            if (waitForNextMesure == true)
            {
                Serial.println(" -> Waiting for Recording \n");
                trackState[track] = WAITING_FOR_RECORDING;
                ButtonLights::setTrackState(track, ButtonLights::WAITING);
            }
            else
            {
                trackState[track] = RECORDING;
                ButtonLights::setTrackState(track, ButtonLights::RECORDING);
            }
            break;

        case PAUSED:
        Serial.print("Paused");
            if (waitForNextMesure == true)
            {
                Serial.println(" -> Waiting for Playing \n");
                trackState[track] = WAITING_FOR_PLAYING;                
                ButtonLights::setTrackState(track, ButtonLights::WAITING);
            }
            else
            {
                trackState[track] = PLAYING;
                ButtonLights::setTrackState(track, ButtonLights::PLAYING);
            }
            break;

        case PLAYING:
        Serial.print("Playing");
            if (waitForNextMesure == true)
            {
                Serial.println(" -> Waiting for Pausing\n");
                trackState[track] = WAITING_FOR_PAUSING;
                ButtonLights::setTrackState(track, ButtonLights::WAITING);
            }
            else
            {
                trackState[track] = PAUSED;
                ButtonLights::setTrackState(track, ButtonLights::PAUSED);
            }
            break;

        case RECORDING:
        Serial.print("Recording");
            if (waitForNextMesure == true)
            {
                Serial.print(" -> Waiting for Pausing\n");
                trackState[track] = WAITING_FOR_PAUSING;
                ButtonLights::setTrackState(track, ButtonLights::WAITING);
            }
            else
            {
                trackState[track] = PAUSED;
                ButtonLights::setTrackState(track, ButtonLights::PAUSED);
            }
            break;

        case WAITING_FOR_PLAYING:
            Serial.print("Waiting for Playing");
            trackState[track] = oldTrackState[track];
            
            break;

        case WAITING_FOR_RECORDING:
            Serial.print("Waiting for Recording");
            trackState[track] = oldTrackState[track];
            if (oldTrackState[track] == EMPTY)
            {
                Serial.println(" -> Empty \n");
                ButtonLights::setTrackState(track, ButtonLights::EMPTY);
            }
            else if (oldTrackState[track] == PAUSED)
            {
                Serial.println(" -> Paused\n");
                ButtonLights::setTrackState(track, ButtonLights::PAUSED);
            }
            else if (oldTrackState[track] == RECORDING)
            {
                Serial.println(" -> Recording\n");
                ButtonLights::setTrackState(track, ButtonLights::RECORDING);
            }
            break;

        case WAITING_FOR_PAUSING:
            Serial.print("Waiting for Pausing");
            trackState[track] = oldTrackState[track];
            // TODO update Lighting
            break;

        default:
            Serial.print("ERROR: unexpected status in Select_Track_Start_Stop (");
            Serial.println(trackState[track]);

            break;
        }
    break;
    case Select_Track_Play_Rec:
        switch (trackState[track])
        {
        case EMPTY:
            if (waitForNextMesure == true)
            {
                trackState[track] = WAITING_FOR_RECORDING;
                // TODO update Lighting
            }
            else
            {
                trackState[track] = RECORDING;
            }
            break;

        case PAUSED:
            if (waitForNextMesure == true)
            {
                trackState[track] = WAITING_FOR_RECORDING;
                // TODO update Lighting
            }
            else
            {
                trackState[track] = RECORDING;
            }
            break;

        case PLAYING:
            if (waitForNextMesure == true)
            {
                trackState[track] = WAITING_FOR_RECORDING;
                // TODO update Lighting
            }
            else
            {
                trackState[track] = RECORDING;
            }
            break;

        case RECORDING:
            if (waitForNextMesure == true)
            {
                trackState[track] = WAITING_FOR_PLAYING;
                // TODO update Lighting
            }
            else
            {
                trackState[track] = PLAYING;
            }
            break;

        case WAITING_FOR_PLAYING:
            trackState[track] = oldTrackState[track];
            // TODO update Lighting
            break;

        case WAITING_FOR_RECORDING:
            trackState[track] = oldTrackState[track];
            // TODO update Lighting
            break;

        case WAITING_FOR_PAUSING:
            trackState[track] = oldTrackState[track];
            // TODO update Lighting
            break;

        default:
            Serial.println("ERROR: unexpected status in Select_Track_Play_Rec");
            break;
        }
    break;

    case All_Start_Stop:  // DEBUG: force an update of the current state
        Serial.print("Forcing Update");
        updateStatus();
        break;

    default:
        Serial.print("not Implemented Function called. (");
        Serial.print(function);
        Serial.println(")");
        break;
    }
    if (waitForNextMesure == false)
    {
        updateStatus(); // do it right away otherwise the update command will get triggered form the myMidi Module.
        
    }

    else // other functions
    {
        switch (function)
        {
        }
    }
}

void updateStatus(void)
{
    for (int track = 0; track < 5; track++)
    {
        if (trackState[track] != oldTrackState[track]) // only if something changed
        {
            Serial.print(" -> ");
            goToTargetTrack(track);
            switch (trackState[track])
            {
            case EMPTY:
                // do nothing
                break;

            case PAUSED: // it was Playing or recording and should get paused
                Serial.print("Paused");
                addMidiCommandToQueue(getTargetTrackCC(Stop), 127);
                addMidiCommandToQueue(getTargetTrackCC(Stop), 0);
                break;

            case WAITING_FOR_PAUSING: // same as Paused, except the aditional state change
                Serial.print("\nWaiting for Pausing -> paused");
                trackState[track] = PAUSED;
                addMidiCommandToQueue(getTargetTrackCC(Stop), 127);
                addMidiCommandToQueue(getTargetTrackCC(Stop), 0);
                ButtonLights::setTrackState(track, ButtonLights::PAUSED);
                break;

            case PLAYING: // it was paused and needs to be started.
                Serial.print("Playing");
                addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                break;

            case WAITING_FOR_PLAYING: // do the same as with playing, except the aditional state change
                Serial.print("\nWaiting for Playing -> Playing");
                trackState[track] = PLAYING;
                addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                ButtonLights::setTrackState(track, ButtonLights::PLAYING);
                break;

            case RECORDING:                        // it was paused or not recorded yet and needs to be recording
                Serial.print("Recording"); 
                if (oldTrackState[track] == EMPTY) // start the track, since it is empty it will start recording automatically
                {
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                }
                else if (oldTrackState[track] == PAUSED) // start it twice form pause, once to start playing and a second time to record
                {
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                }
                else
                {
                    Serial.println("ERROR: unexpected state switch for Recording");
                }
                break;

            case WAITING_FOR_RECORDING:            // same as Recording, except the aditional state change
                Serial.print("\nWaiting for Recording -> Recording");
                trackState[track] = RECORDING;
                if (oldTrackState[track] == EMPTY) // start the track, since it is empty it will start recording automatically
                {
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                    
                }
                else if (oldTrackState[track] == PAUSED) // start it twice form pause, once to start playing and a second time to record
                {
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
                    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);
                }
                else
                {
                    Serial.println("ERROR: unexpected state switch for Waiting for recording");
                }
                ButtonLights::setTrackState(track, ButtonLights::RECORDING);
                
                break;

            default:
                Serial.println("ERROR: unexpected state switch");
                break;
            }
        }
        oldTrackState[track] = trackState[track];
    }
    Serial.println();
    Serial.println();
    
}

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
            addMidiCommandToQueue(getTargetTrackCC(Inc), 127);
            addMidiCommandToQueue(getTargetTrackCC(Inc), 0);
        }

        else if (difference == -3 or difference == 2)
        {
            addMidiCommandToQueue(getTargetTrackCC(Inc), 127);
            addMidiCommandToQueue(getTargetTrackCC(Inc), 0);

            addMidiCommandToQueue(getTargetTrackCC(Inc), 127);
            addMidiCommandToQueue(getTargetTrackCC(Inc), 0);
        }

        else if (difference == -2 or difference == 3)
        {
            addMidiCommandToQueue(getTargetTrackCC(Dec), 127);
            addMidiCommandToQueue(getTargetTrackCC(Dec), 0);

            addMidiCommandToQueue(getTargetTrackCC(Dec), 127);
            addMidiCommandToQueue(getTargetTrackCC(Dec), 0);
        }

        else if (difference == -1 or difference == 4)
        {
            addMidiCommandToQueue(getTargetTrackCC(Dec), 127);
            addMidiCommandToQueue(getTargetTrackCC(Dec), 0);
        }
    }
}

/*

void startTrack(uint8_t track)
{
    goToTargetTrack(track);
    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 127);
    addMidiCommandToQueue(getTargetTrackCC(Play_Rec), 0);

    trackPlaying[track - 1] = true;
    trackHasRecording[track - 1] = true;
    Serial.print("Track Nr ");
    Serial.print(track);
    Serial.println(" Started");
}

void stopTrack(uint8_t track)
{
    goToTargetTrack(track);
    addMidiCommandToQueue(getTargetTrackCC(Stop), 127);
    addMidiCommandToQueue(getTargetTrackCC(Stop), 0);

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
        if (((startWithOverdub == true) & (trackHasRecording[track - 1] == true))) // press it twice to go into overdub if its allready recorded
        {
            startTrack(track); // can also be used to start overdub.
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (((trackHasRecording[i] == true) & (trackPlaying[i] == false)))
        {
            if ((TracksToStart & ((int)pow(2, i))) && (i != track - 1)) // is the this Track supposed to be started and isnt the pressed one
            {
                startTrack(i + 1);
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
    }

    for (int i = 0; i < 5; i++)
    {
        if (((trackHasRecording[i] == true) & (trackPlaying[i] == true)))
        {
            if ((TracksToStop & ((int)pow(2, i))) && (i != track - 1)) // is the this Track supposed to be started and isnt the pressed one
            {
                stopTrack(i + 1);
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
        }
    }
}

*/

} // namespace FunctionHandler