#include <Arduino.h>
#include "inputs.h"
#include "configEditor.h"
#include "display.h"

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

void buttonPressed(uint32_t button)
{
    switch (button)
    {
    case 0:
        bankUpPressed();
        break;

    case 1:
        bankDownPressed();
        break;

    default:
        break;
    }
}