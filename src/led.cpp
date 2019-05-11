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

// test Leds
void Led::Test(void)
{
    // change all the LEDs in 1.5 seconds
    int microsec = 1500000 / leds.numPixels();

    setMasterBrightness(20);

    colorWipe(RGBW_CODE_RED, microsec);
    colorWipe(RGBW_CODE_GREEN, microsec);
    colorWipe(RGBW_CODE_BLUE, microsec);
    colorWipe(RGBW_CODE_YELLOW, microsec);
    colorWipe(RGBW_CODE_PINK, microsec);
    colorWipe(RGBW_CODE_ORANGE, microsec);
    colorWipe(RGBW_CODE_WHITE, microsec);
}

// wipe color thru all Leds
void Led::colorWipe(int color, int wait)
{
    for (int i = 0; i < leds.numPixels(); i++)
    {
        leds.setPixel(i, (color & 0x000000FF / 255 * masterBrightness) | (color & 0x0000FF00 / 255 * masterBrightness) | (color & 0x00FF0000 / 255 * masterBrightness) | (color & 0xFF000000 / 255 * masterBrightness) );
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
Led::Segment::Segment(uint8_t newStart, u_int8_t newEnd)
{
    start = newStart;
    end = newEnd;
    brightness = 255;
}

// Overload Constructor
Led::Segment::Segment(uint8_t newStart, u_int8_t newEnd, uint8_t newBrightness)
{
    start = newStart;
    end = newEnd;
    brightness = newBrightness;
}

// --------------------------------------- set functions -----------------------------------------------//

// set start id for Led Segment
void Led::Segment::setStart(uint8_t newStart)
{
 start = newStart;
}

// set start id for Led Segment
void Led::Segment::setEnd(uint8_t newEnd)
{
 start = newEnd;
}

// set start id for Led Segment
void Led::Segment::setBrightness(uint8_t newBrightness)
{
 start = newBrightness;
}

// --------------------------------------- get functions -----------------------------------------------//

// get start id for Led Segment
uint8_t Led::Segment::getStart() const
{
    return start;
}

// get end id for Led Segment
uint8_t Led::Segment::getEnd() const
{
    return end;
}

// get end id for Led Segment
uint8_t Led::Segment::getBrightness() const
{
    return brightness;
}