#include <Arduino.h>
#include "Pins.h"
#include "TimedTasks.h"
#include "functionHandler.h"
#include "inputs.h"

namespace inputs
{

// ENABLE INPUT-PULLDOWN
// Set Pint as GPIO
#define DIGITALINPUT PORT_PCR_PE | PORT_PCR_MUX(1)

#define ANALOGINPUT PORT_PCR_MUX(1)

volatile uint32_t debouncedInputBuffer = 0;
volatile uint32_t LastDebouncedInputBuffer = 0;
volatile uint32_t wasPressedBuffer = 0;

void initInputs(void)
{

    // requires TimedTasks::init();

    BTN_BK_UP_CONFIG = DIGITALINPUT;
    BTN_BK_DWN_CONFIG = DIGITALINPUT;
    BTN_MODE_CONFIG = DIGITALINPUT;
    BTN_SAVE_CONFIG = DIGITALINPUT;
    BTN_BACK_CONFIG = DIGITALINPUT;
    BTN_SELECT_CONFIG = DIGITALINPUT;

    ENCODER_CLK_CONFIG = DIGITALINPUT;
    // ENCODER_DT_CONFIG = DIGITALINPUT; // Disabled for Debug

    PEDAL_CONFIG = ANALOGINPUT;

    TRACK1_PLAY_CONFIG = DIGITALINPUT;
    TRACK1_OVD_CONFIG = DIGITALINPUT;
    TRACK2_PLAY_CONFIG = DIGITALINPUT;
    TRACK2_OVD_CONFIG = DIGITALINPUT;
    TRACK3_PLAY_CONFIG = DIGITALINPUT;
    TRACK3_OVD_CONFIG = DIGITALINPUT;
    TRACK4_PLAY_CONFIG = DIGITALINPUT;
    TRACK4_OVD_CONFIG = DIGITALINPUT;
    TRACK5_PLAY_CONFIG = DIGITALINPUT;
    TRACK5_OVD_CONFIG = DIGITALINPUT;

    CSTM_SW1_CONFIG = DIGITALINPUT;
    CSTM_SW2_CONFIG = DIGITALINPUT;
    CSTM_SW3_CONFIG = DIGITALINPUT;
    CSTM_SW4_CONFIG = DIGITALINPUT;
    CSTM_SW5_CONFIG = DIGITALINPUT;
}



static uint32_t inputBuffer = 0;
static uint32_t lastInputBuffer = 0;

void InputsISR(void)
{

    inputBuffer = ((BTN_BK_UP_PINMASK) ? 1 : 0) | (((BTN_BK_DWN_PINMASK) ? 1 : 0) << 1) | (((BTN_MODE_PINMASK) ? 1 : 0) << 2) | (((BTN_BACK_PINMASK) ? 1 : 0) << 3) | (((BTN_SAVE_PINMASK) ? 1 : 0) << 4) | (((BTN_SELECT_PINMASK) ? 1 : 0) << 5) | (((TRACK1_PLAY_PINMASK) ? 1 : 0) << 6) | (((TRACK1_OVD_PINMASK) ? 1 : 0) << 7) | (((TRACK2_PLAY_PINMASK) ? 1 : 0) << 8) | (((TRACK2_OVD_PINMASK) ? 1 : 0) << 9) | (((TRACK3_PLAY_PINMASK) ? 1 : 0) << 10) | (((TRACK3_OVD_PINMASK) ? 1 : 0) << 11) | (((TRACK4_PLAY_PINMASK) ? 1 : 0) << 12) | (((TRACK4_OVD_PINMASK) ? 1 : 0) << 13) | (((TRACK5_PLAY_PINMASK) ? 1 : 0) << 14) | (((TRACK5_OVD_PINMASK) ? 1 : 0) << 15) | (((CSTM_SW1_PINMASK) ? 1 : 0) << 16) | (((CSTM_SW2_PINMASK) ? 1 : 0) << 17) | (((CSTM_SW3_PINMASK) ? 1 : 0) << 18) | (((CSTM_SW4_PINMASK) ? 1 : 0) << 19) | (((CSTM_SW5_PINMASK) ? 1 : 0) << 20);
    // if the buffer didn't change, eighter because nothing happended,
    // or because the previously pressed Button has finished bouncing
    // write the current state to the debounced buffer

    if (inputBuffer == lastInputBuffer)
    {
        debouncedInputBuffer = inputBuffer;
    }

    // write the current Buffer as LastBuffer for the next time
    lastInputBuffer = inputBuffer;

    wasPressedBuffer = wasPressedBuffer | ((LastDebouncedInputBuffer xor debouncedInputBuffer) & debouncedInputBuffer); // search positive flanks and add them to Buffer

    LastDebouncedInputBuffer = debouncedInputBuffer;
}

uint32_t getInputs(void)
{
    return debouncedInputBuffer;
}

void printInputs(uint32_t buffer)
{
    for (int i = 0; i <= 19; i++)
    {
        Serial.print(bitRead(buffer, i));
    }
    Serial.println(bitRead(buffer, 20));
}

uint32_t getPressedButton(void)
{
    uint32_t buf = wasPressedBuffer; // no longer volatile

    uint32_t lsb = (((buf | (buf - 1)) ^ (buf - 1))); // in case there are more then one

    wasPressedBuffer = wasPressedBuffer & ~lsb; // reset the found button

    return lsb; // return it

    // http://www.goldsborough.me/bits/c++/low-level/problems/2015/10/11/23-52-02-bit_manipulation/
}

void checkInputs(void)
{
    uint32_t buf = wasPressedBuffer;

    if (buf != 0)
    {
        uint32_t button = getPressedButton();

        inputs::buttonPressed(button);
    }
}

bool bottonsWerePressed(uint32_t btnMask)
{
    if ((~wasPressedBuffer & btnMask))
    {
        return false; // comparison was not equal to 0 (true), so a asked button was not pressed
    }
    else // the comparison resulted in a 0 (false), so the asked buttons were pressed
    {
        wasPressedBuffer = wasPressedBuffer & ~btnMask; // reset the asked buttons
        return true;
    }
}

void buttonPressed(uint32_t button)
{
    using namespace FunctionHandler;

    if (button > BTN_SELECT)
    {
        footButtonPressed((int)log2(button >> 6)); // get Footswitch Number (0 - 14)
    }
    else
    {
        switch (button)
        {
        case BTN_BK_UP:
            bankUpPressed();
            break;

        case BTN_BK_DWN:
            bankDownPressed();
            break;

        case BTN_MODE:
            modePressed();
            break;

        case BTN_BACK:
            backPressed();
            break;

        case BTN_SAVE:
            savePressed();
            break;

        case BTN_SELECT:
            selectPressed();
            break;

        default:
            break;
        }
    }
}
} // end namespace