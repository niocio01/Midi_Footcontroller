// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

#include "i2c_t3.h"
#include "i2c_mux.h"

#include <Arduino.h>
#include <U8g2lib.h>

//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// End of constructor list

void displaySetup(void)
{

    byte response = 0;

    Wire.begin();
    Serial.print("i2c Clock speed: ");
    // Serial.print (Wire.getClock() );
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

        u8g2.clearBuffer();                  // clear the internal memory
        u8g2.setFont(u8g2_font_profont12_tf  );  // choose a suitable font
        u8g2.drawStr(0, 8, "Hello World!"); // write something to the internal memory
        u8g2.sendBuffer();                   // transfer internal memory to the display
        //delay(1000);
    }
}

    // #define SCREEN_WIDTH 128 // OLED display width, in pixels
    // #define SCREEN_HEIGHT 64 // OLED display height, in pixels
    //
    // #define DISPLAY1 0x3C
    //
    // // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
    // #define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
    // Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    //
    // void displaySetup(void) {
    //
    //     byte response = 0;
    //
    //     Wire.begin();
    //     Serial.print("i2c Clock speed: ");
    //     // Serial.print (Wire.getClock() );
    //     Serial.println(" Hz");
    //
    //
    //
    //     for (int i = 2 ; i <= 6 ; i++)
    //     {
    //         selectMuxPort(i);
    //
    //         Wire.beginTransmission(0x3C);
    //         response = Wire.endTransmission();
    //         if (response == 0)
    //         {
    //             Serial.println("Display Connected");
    //         }
    //         else
    //         {
    //             Serial.println("Display not reachable!");
    //         }
    //
    //         display.begin(SSD1306_EXTERNALVCC, DISPLAY1);
    //
    //         display.clearDisplay();
    //         display.setTextSize(2);
    //         display.setTextColor(WHITE);
    //         display.setCursor(10, 10);
    //         display.print("Display ");
    //         display.println(i-1);
    //         display.display();
    //     }
    // }