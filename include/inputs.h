#ifndef INPUTS_H
#define INPUTS_H

#define BTN_BK_UP       (1 << 0)
#define BTN_BK_DWN      (1 << 1)
#define BTN_MODE        (1 << 2)
#define BTN_BACK        (1 << 3)
#define BTN_SAVE        (1 << 4)
#define BTN_SELECT      (1 << 5)

#define TRACK1_PLAY     (1 << 6)
#define TRACK1_OVD      (1 << 7)
#define TRACK2_PLAY     (1 << 8)
#define TRACK2_OVD      (1 << 9)
#define TRACK3_PLAY     (1 << 10)
#define TRACK3_OVD      (1 << 11)
#define TRACK4_PLAY     (1 << 12)
#define TRACK4_OVD      (1 << 13)
#define TRACK5_PLAY     (1 << 14)
#define TRACK5_OVD      (1 << 15)

#define CSTM_SW1        (1 << 16)
#define CSTM_SW2        (1 << 17)
#define CSTM_SW3        (1 << 18)
#define CSTM_SW4        (1 << 19)
#define CSTM_SW5        (1 << 20)

void initInputs (void);

void InputsISR(void);

uint32_t getInputs(void);

void printInputs(uint32_t buffer);

void checkInputs(void);

bool bottonsWerePressed(uint32_t btnMask);


// function to rout to the corresponding button Function
void buttonPressed(uint32_t button);


#endif