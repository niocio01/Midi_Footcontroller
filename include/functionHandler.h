/*
functionHandler.h:
manage the actions to take when a specific button is pressed
 */


#ifndef FUNCTION_HANDLER_H
#define FUNCTION_HANDLER_H

#include <Arduino.h>

namespace FunctionHandler
{

typedef enum trackState
{
    INIT,
    EMPTY,
    PAUSED,
    PLAYING,
    RECORDING,
    WAITING_FOR_PLAYING,
    WAITING_FOR_RECORDING,
    WAITING_FOR_PAUSING,
} trackState_t;

void footButtonPressed(uint8_t button);

void updateStatus(void);

void bankUpPressed(void);

void bankDownPressed(void);

void modePressed(void);

void backPressed(void);

void savePressed(void);

void selectPressed(void);

void goToTargetTrack(uint8_t targetTrack);

/*

void startTrack(uint8_t track);

void stopTrack(uint8_t track);

void startOnStart(uint8_t track, bool startWithOverdub);

void stopOnStart(uint8_t track);

void stopOnStop(uint8_t track);

*/

} // end namespace

#endif // !FUNCTION_HANDLER_H