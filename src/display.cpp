// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

#include "i2c_t3.h"
#include "i2c_mux.h"

#include <Arduino.h>
#include <U8g2lib.h>

#include "Pins.h"
#include "configEditor.h"

//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

bool updateDisplayNeccessary = true;

void displaySetup(void)
{

    byte response = 0;

    Wire.begin();
    Serial.print("i2c Clock speed: ");
    Serial.print (Wire.getClock() );
    Serial.println(" Hz");

    for (int i = 2; i <= 6; i++)
    {
        selectMuxPort(i);

        Wire.beginTransmission(0x3C);
        response = Wire.endTransmission();
        if (response == 0)
        {
            Serial.println("Display Connected");
        }
        else
        {
            Serial.println("Display not reachable!");
        }

        u8g2.begin();

        u8g2.clearBuffer();                   // clear the internal memory
        u8g2.setFont(u8g2_font_profont12_tf); // choose a suitable font
        u8g2.drawStr(0, 8, "Hello World!");   // write something to the internal memory
        u8g2.sendBuffer();                    // transfer internal memory to the display
                                              //delay(1000);
    }
}

void drawBank()
{
    u8g2.setFont(u8g2_font_profont29_tf);
    if (getBank() < 10)
    {
        u8g2.setCursor(18, 22);
    }
    else
    {
        u8g2.setCursor(9, 22);
    }
    u8g2.print("Bank ");
    u8g2.drawHLine(0,27,128);
    u8g2.drawHLine(0,28,128);
    u8g2.print(getBank());
}

void setUpdateFlag(void)
{
    updateDisplayNeccessary = true;
}

void updateDisplay(void)
{
    

    if (updateDisplayNeccessary == true)
    {
        updateDisplayNeccessary = false;

        selectMuxPort(2); // main display
        u8g2.clearBuffer(); // clear the internal memory

        drawBank();

        u8g2.sendBuffer(); // transfer internal memory to the display
    }
}