#include <Arduino.h>
#include "config.h"

extern config_t config;

uint8_t getBank (void)
{
    return config.globalSettings.currentBank;
}

void changeBank(uint8_t newBank)
{
    if (newBank > 0 and newBank < 100)
    {
        writeBank(config.globalSettings.currentBank);
        config.globalSettings.currentBank = newBank;
        readBank(newBank);
    }
}
