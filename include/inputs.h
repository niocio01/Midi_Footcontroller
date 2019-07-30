/*
inputs.h:
get all the inputs form there corresponding pins, Debounce them,
check if a button has ben pressed (pushed and released)
write all the Inputs into big buffers to simplify working with them.

 */

#ifndef INPUTS_H
#define INPUTS_H

namespace inputs
{

const int BTN_BK_UP       (1 << 0);
const int BTN_BK_DWN      (1 << 1);
const int BTN_MODE        (1 << 2);
const int BTN_BACK        (1 << 3);
const int BTN_SAVE        (1 << 4);
const int BTN_SELECT      (1 << 5);

const int TRACK1_PLAY     (1 << 6);
const int TRACK1_OVD      (1 << 7);
const int TRACK2_PLAY     (1 << 8);
const int TRACK2_OVD      (1 << 9);
const int TRACK3_PLAY     (1 << 10);
const int TRACK3_OVD      (1 << 11);
const int TRACK4_PLAY     (1 << 12);
const int TRACK4_OVD      (1 << 13);
const int TRACK5_PLAY     (1 << 14);
const int TRACK5_OVD      (1 << 15);

const int CSTM_SW1        (1 << 16);
const int CSTM_SW2        (1 << 17);
const int CSTM_SW3        (1 << 18);
const int CSTM_SW4        (1 << 19);
const int CSTM_SW5        (1 << 20);

void initInputs (void);

void InputsISR(void);

uint32_t getInputs(void);

void printInputs(uint32_t buffer);

void checkInputs(void);

bool bottonsWerePressed(uint32_t btnMask);


// function to rout to the corresponding button Function
void buttonPressed(uint32_t button);

}

#endif