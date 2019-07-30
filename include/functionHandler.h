/*
functionHandler.h:
manage the actions to take when a specific button is pressed
 */

#ifndef FUNCTION_HANDLER_H
#define FUNCTION_HANDLER_H

#include <Arduino.h>

namespace FunctionHandler
{

void bankUpPressed(void);

void bankDownPressed(void);

void modePressed(void);

void backPressed(void);

void savePressed(void);

void selectPressed(void);

void footButtonPressed(uint8_t button);

bool * getPlayingTracksPointer(void);

} // end namespace

#endif // !FUNCTION_HANDLER_H