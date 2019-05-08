#include <WS2812Serial.h>
#include "led.h"

const int numled =5;
const int pin = 8;

// Usable pins:
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33

byte drawingMemory[numled*3];         //  3 bytes per LED
DMAMEM byte displayMemory[numled*12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

void initLed(void)
{

    leds.begin();
}

void ledTest(void)
{
 // change all the LEDs in 1.5 seconds
  int microsec = 1500000 / leds.numPixels();

  colorWipe(this_RED, microsec);
  colorWipe(this_GREEN, microsec);
  colorWipe(this_BLUE, microsec);
  colorWipe(this_YELLOW, microsec);
  colorWipe(this_PINK, microsec);
  colorWipe(this_ORANGE, microsec);
  colorWipe(this_WHITE, microsec);
}

void colorWipe(int color, int wait) {
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}
