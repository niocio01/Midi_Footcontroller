#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "i2c_mux.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define DISPLAY1 0x3C

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displaySetup(void) {

    byte response = 0;

    Wire.begin();
    Serial.print("i2c Clock speed: ");
    // Serial.print (Wire.getClock() );
    Serial.println(" Hz");

    selectMuxPort(2);

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

    display.begin(DISPLAY1);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.println("Display 3");
    display.display();
}