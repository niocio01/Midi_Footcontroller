// #include <Wire.h>
#include "i2c_t3.h"

#include <arduino.h>

// #include "twi.h"  // from Wire library, so we can do bus scanning

#define TCAADDR 0x70

void selectMuxPort(uint8_t adress)
{
    byte response = 0;
    if (adress > 7)
        return;

    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << adress);
    response = Wire.endTransmission();

    if (response == 0)
    {
        // Serial.print("MUX Set to Port ");
        // Serial.println(adress);
    }
    else
    {
        Serial.println("Problem with i2c MUX Port setting.");
    }
}