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
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2A(U8G2_R0, /* reset=*/20); // Main Display with Reset Pin

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2B(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // Analog Pedal Display

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2C(U8G2_R0); // Small Special Button Displays

bool updateDisplayNeccessary = false;

void displaySetup(void)
{

    byte response = 0;

    Wire.begin();
    Serial.print("i2c Clock speed: ");
    Serial.print(Wire.getClock());
    Serial.println(" Hz");

    for (int i = 4; i <= 6; i++)
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

        u8g2C.begin();
        u8g2C.clearBuffer();
        u8g2C.setFont(u8g2_font_profont15_tf);
        u8g2C.setFontPosCenter();
        u8g2C.setCursor((128 - u8g2C.getStrWidth("Custom Button 1")) / 2, 32 / 2);
        u8g2C.print("Custom Button ");
        u8g2C.print(i - 3);
        u8g2C.sendBuffer();
    }

    selectMuxPort(3);

    u8g2B.begin();
    u8g2B.clearBuffer();
    u8g2B.setFont(u8g2_font_profont15_tf);
    u8g2B.setFontPosCenter();
    u8g2B.setCursor((128 - u8g2B.getStrWidth("Analog Pedal")) / 2, 64 / 2);
    u8g2B.print("Analog Pedal");
    u8g2B.sendBuffer();

    char startMessage1[] = "Midi";
    char startMessage2[] = "Footcontroller";
    char startMessage3[] = "by Nico Zuber";

    selectMuxPort(2);

    u8g2A.begin();
    u8g2A.clearBuffer();
    u8g2A.setFont(u8g2_font_profont17_tf);
    u8g2A.setFontPosTop();
    u8g2A.drawStr(((128 - u8g2A.getStrWidth(startMessage1)) / 2), 4, startMessage1);
    u8g2A.drawStr(((128 - u8g2A.getStrWidth(startMessage2)) / 2), u8g2A.getAscent() + abs(u8g2A.getDescent()) + 2, startMessage2);

    u8g2A.setFont(u8g2_font_profont12_tf);
    u8g2A.drawStr(((128 - u8g2A.getStrWidth(startMessage3)) / 2), 40, startMessage3);

    u8g2A.sendBuffer();

    
    for (int i = 1; i <= 128; i++)
    {
        u8g2A.drawPixel(i, 62);
        u8g2A.drawPixel(i, 63);
        u8g2A.sendBuffer();
        delay(10);
    }
}

void drawBank()
{
    uint8_t width = 0;

    selectMuxPort(2);    // main display
    u8g2A.clearBuffer(); // clear the internal memory

    u8g2A.setFont(u8g2_font_profont29_tf);
    if (getBank() < 10)
    {
        width = u8g2A.getStrWidth("Bank 0");
        u8g2A.setCursor((128 - width) / 2, 2);
    }
    else
    {
        width = u8g2A.getStrWidth("Bank 00");
        u8g2A.setCursor((128 - width) / 2, 2);
    }
    u8g2A.print("Bank ");
    u8g2A.print(getBank());
    u8g2A.drawHLine(0, u8g2A.getAscent() + abs(u8g2A.getDescent()), 128);
    u8g2A.drawHLine(0, u8g2A.getAscent() + abs(u8g2A.getDescent()) + 1, 128);

    u8g2A.sendBuffer();
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

        drawBank();
    }
}