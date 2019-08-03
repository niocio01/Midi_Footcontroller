#include <WS2812Serial.h>
#include "led.h"

// Usable pins:
//   Teensy LC:   1, 4, 5, 24
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33

namespace Led
{

uint8_t masterBrightness = 255;

byte drawingMemory[numLed * 4];         //  4 bytes per LED
DMAMEM byte displayMemory[numLed * 16]; // 16 bytes per LED

// create new Led (WS2812Serial) Object
WS2812Serial leds(numLed, displayMemory, drawingMemory, pin, WS2812_RGBW);

// initiate the Led Strip
void init(void)
{
    leds.begin();
    for (int i = 0; i < numLed; i++)
    {
        leds.setPixel(i, 0, 0, 0, 0);
    }
    leds.show();
    Serial.println("Leds Reset");
}

// send current frambuffer to leds
void update(void)
{
    leds.show();
}

// set Brightness multiplier for all Leds
void setMasterBrightness(uint8_t newBrightness)
{
    masterBrightness = newBrightness;
}

// get the number of Leds on the strip
uint8_t getNum(void)
{
    return numLed;
}

int getColorCode(Colors_t color)
{
    using namespace Led;

    switch (color)
    {
    case RED:
        return RGBW_RED;
        break;

    case GREEN:
        return RGBW_GREEN;
        break;

    case BLUE:
        return RGBW_BLUE;
        break;

    case WHITE:
        return RGBW_WHITE;
        break;

    case BLACK:
        return RGBW_BLACK;
        break;

    case YELLOW:
        return RGBW_YELLOW;
        break;

    case VIOLET:
        return RGBW_VIOLET;
        break;

    case ORANGE:
        return RGBW_ORANGE;
        break;

    default:
        return RGBW_WHITE;
        break;
    }
}

// test Leds
void Test(void)
{
    // change all the LEDs in 1.5 seconds
    int microsec = 1500000 / leds.numPixels();

    colorWipe(RGBW_RED, microsec);
    colorWipe(RGBW_GREEN, microsec);
    colorWipe(RGBW_BLUE, microsec);
    colorWipe(RGBW_WHITE, microsec);
    colorWipe(RGBW_PINK, microsec);
    colorWipe(RGBW_ORANGE, microsec);
    colorWipe(RGBW_YELLOW, microsec);
}

// wipe color thru all Leds
void colorWipe(int color, int wait)
{
    for (int i = 0; i < leds.numPixels(); i++)
    {
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
Segment::Segment()
{
    start = 0;
    end = numLed;
    brightness = 255;
}

// Overload Constructor
Segment::Segment(uint32_t newStart, uint32_t newEnd)
{
    start = newStart;
    end = newEnd;
    brightness = 255;
}

// Overload Constructor
Segment::Segment(uint32_t newStart, uint32_t newEnd, uint8_t newBrightness)
{
    start = newStart;
    end = newEnd;
    brightness = newBrightness;
}

// --------------------------------------- set functions -----------------------------------------------//

// set start id for Led Segment
void Segment::setStart(uint32_t newStart)
{
    start = newStart;
}

// set start id for Led Segment
void Segment::setEnd(uint32_t newEnd)
{
    end = newEnd;
}

// set start id for Led Segment
void Segment::setBrightness(uint8_t newBrightness)
{
    brightness = newBrightness;
}

//----------------------------------------------------Set All-----------------------------------------------------------------//
// set color of all segment Led's
void Segment::setAll(int color)
{
    for (uint32_t i = start; i <= end; i++)
    {
        leds.setPixel(i+25, ((color >> 24) & 255) * brightness / 255 * masterBrightness / 255, // red
                      ((color >> 16) & 255) * brightness / 255 * masterBrightness / 255,            // green
                      ((color >> 8) & 255) * brightness / 255 * masterBrightness / 255,     // blue
                      (color & 255) * brightness / 255 * masterBrightness / 255);   // white
    }
}

void Segment::setAll(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    for (uint32_t i = start; i <= end; i++)
    {
        leds.setPixel(i+25, red * brightness / 255 * masterBrightness / 255, // red
                      green * brightness / 255 * masterBrightness / 255,  // green
                      blue * brightness / 255 * masterBrightness / 255,   // blue
                      white * brightness / 255 * masterBrightness / 255); // white
    }
}

//----------------------------------------------------Set Led-----------------------------------------------------------------//
// set inidvidual Led of segment
void Segment::setLed(uint32_t id, int color)
{
    leds.setPixel(start + id+25, ((color >> 24) & 255) * brightness / 255 * masterBrightness / 255, // red
                  ((color >> 16) & 255) * brightness / 255 * masterBrightness / 255,              // green
                  ((color >> 8) & 255) * brightness / 255 * masterBrightness / 255,                     // blue
                  (color & 255) * brightness / 255 * masterBrightness / 255);            // white
}

void Segment::setLed(uint32_t id, uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    leds.setPixel(start + id+25, red * brightness / 255 * masterBrightness / 255,
                  green * brightness / 255 * masterBrightness / 255,
                  blue * brightness / 255 * masterBrightness / 255,
                  white * brightness / 255 * masterBrightness / 255);
}

// --------------------------------------- get functions -----------------------------------------------//

// get start id for Led Segment
uint32_t Segment::getStart() const
{
    return start;
}

// get end id for Led Segment
uint32_t Segment::getEnd() const
{
    return end;
}

// get end id for Led Segment
uint8_t Segment::getBrightness() const
{
    return brightness;
}

} // namespace Led