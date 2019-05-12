#include <WS2812Serial.h>
#include "led.h"

// Usable pins:
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33

uint8_t masterBrightness = 255;

byte drawingMemory[Led::numLed * 3];         //  3 bytes per LED
DMAMEM byte displayMemory[Led::numLed * 12]; // 12 bytes per LED

// create new Led (WS2812Serial) Object
WS2812Serial leds(Led::numLed, displayMemory, drawingMemory, Led::pin, WS2812_RGBW);

// initiate the Led Strip
void Led::init(void)
{
    leds.begin();
}

// send current frambuffer to leds
void Led::update(void)
{
    leds.show();
}

// set Brightness multiplier for all Leds
void Led::setMasterBrightness(uint8_t newBrightness)
{
    masterBrightness = newBrightness;
}

// get the number of Leds on the strip
uint8_t Led::getNum(void)
{
    return Led::numLed;
}

// test Leds
void Led::Test(void)
{
   // change all the LEDs in 1.5 seconds
  int microsec = 1500000 / leds.numPixels();

  colorWipe(RGBW_RED, microsec);
  colorWipe(RGBW_GREEN, microsec);
  colorWipe(RGBW_BLUE, microsec);
  colorWipe(RGBW_YELLOW, microsec);
  colorWipe(RGBW_PINK, microsec);
  colorWipe(RGBW_ORANGE, microsec);
  colorWipe(RGBW_WHITE, microsec);
}

// wipe color thru all Leds
void Led::colorWipe(int color, int wait)
{
   for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Segement Class                                                  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------ class Constructors -----------------------------------------------//

// Default Constructor
Led::Segment::Segment()
{
    start = 0;
    end = numLed;
    brightness = 255;
}

// Overload Constructor
Led::Segment::Segment(uint32_t newStart, uint32_t newEnd)
{
    start = newStart;
    end = newEnd;
    brightness = 255;
}

// Overload Constructor
Led::Segment::Segment(uint32_t newStart, uint32_t newEnd, uint8_t newBrightness)
{
    start = newStart;
    end = newEnd;
    brightness = newBrightness;
}

// --------------------------------------- set functions -----------------------------------------------//

// set start id for Led Segment
void Led::Segment::setStart(uint32_t newStart)
{
 start = newStart;
}

// set start id for Led Segment
void Led::Segment::setEnd(uint32_t newEnd)
{
 start = newEnd;
}

// set start id for Led Segment
void Led::Segment::setBrightness(uint8_t newBrightness)
{
 brightness = newBrightness;
}

// set color of all segment Led's
void Led::Segment::setAll(int color)
{
for (uint32_t i = start ; i < end ; i++)
    {
        leds.setPixel(i, ((color >> 16) & 255) * brightness / 255 * masterBrightness / 255,   // red
                         ((color >> 8) & 255)  * brightness / 255 * masterBrightness / 255,   // green
                         (color & 255)         * brightness / 255 * masterBrightness / 255,   // blue
                         ((color >> 24) & 255) * brightness / 255 * masterBrightness / 255 ); // white

    }
}

// set color of all segment Led's
void Led::Segment::setAll(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    for (uint32_t i = start ; i < end ; i++)
    {
        leds.setPixel(i, red   * brightness / 255 * masterBrightness / 255 ,  // red
                         green * brightness / 255 * masterBrightness / 255,  // green
                         blue  * brightness / 255 * masterBrightness / 255,  // blue
                         white * brightness / 255 * masterBrightness / 255); // white

    }
}

// set inidvidual Led of segment
void Led::Segment::setLed(uint32_t id, int color)
{
    leds.setPixel(start + id, ((color >> 16) & 255) * brightness / 255 * masterBrightness / 255,   // red
                              ((color >> 8) & 255)  * brightness / 255 * masterBrightness / 255,   // green
                              (color & 255)         * brightness / 255 * masterBrightness / 255,   // blue
                              ((color >> 24) & 255) * brightness / 255 * masterBrightness / 255 ); // white
}

// set inidvidual Led of segment
void Led::Segment::setLed(uint32_t id, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    leds.setPixel(start + id, red *   brightness / 255 * masterBrightness / 255,
                              green * brightness / 255 * masterBrightness / 255,
                              blue *  brightness / 255 * masterBrightness / 255,
                              white*  brightness / 255 * masterBrightness / 255);

}

// --------------------------------------- get functions -----------------------------------------------//

// get start id for Led Segment
uint32_t Led::Segment::getStart() const
{
    return start;
}

// get end id for Led Segment
uint32_t Led::Segment::getEnd() const
{
    return end;
}

// get end id for Led Segment
uint8_t Led::Segment::getBrightness() const
{
    return brightness;
}