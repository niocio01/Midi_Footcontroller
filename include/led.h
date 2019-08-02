/*
led.h:
provide simple functions to controll the RGBWLed's
 */

#ifndef LED_H
#define LED_H

#include <Arduino.h>



// create namespace to avoid name reusing
namespace Led 
{


const int numLed = 48+25; //48
const int pin = 8;

// create color type, used in Config reading / setting
typedef enum Colors
{
    RED = 1,
    GREEN,
    BLUE,
    WHITE,
    BLACK,
    YELLOW,
    ORANGE,
    VIOLET,
} Colors_t;


// define colors for easy reference
#define RGBW_RED    0xFF000000
#define RGBW_GREEN  0x00FF0000
#define RGBW_BLUE   0x0000FF00
#define RGBW_WHITE  0x000000FF
#define RGBW_YELLOW 0xFFFF0000
#define RGBW_PINK   0xFF108804
#define RGBW_ORANGE 0xE0580000
#define RGBW_VIOLET 0xC000FF00

#define RGBW_BLACK 0x00000000


// non class functions

// initiate the Led Strip
void init(void);

// send current frambuffer to leds
void update(void);

// set Brightness multiplier for all Leds
void setMasterBrightness(uint8_t newBrightness);

// get the number of Leds on the strip
uint8_t getNum(void);

int getColorCode(Colors_t color);

// test Leds
void Test(void);

// wipe color thru all Leds
void colorWipe(int color, int wait);


// led class
class Segment
{

public:
// class Constructors

    // Default Constructor
    Segment();

    // Overload Constructor
    Segment(uint32_t newStart, uint32_t newEnd);

    // Overload Constructor
    Segment(uint32_t newStart, uint32_t newEnd, uint8_t newBrightness);

// set functions

    // set start id for Led Segment
    void setStart(uint32_t newStart);

    // set end id for Led Segment
    void setEnd(uint32_t newEnd);

    // set Brightness for Led Segment
    void setBrightness(uint8_t newBrightness);

    // set color of all segment Led's
    void setAll(int color);

    // set color of all segment Led's
    void setAll(uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

    // set inidvidual Led of segment
    void setLed(uint32_t id, int color);

    // set inidvidual Led of segment
    void setLed(uint32_t id, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);



// get functions

    // get start id for Led Segment
    uint32_t getStart() const;

    // get end id for Led Segment
    uint32_t getEnd() const;

    // get Brightness of Led Segment
    uint8_t getBrightness() const;

private:
    uint32_t start;      // start id of Led Segment
    uint32_t end;        // end id of Led Segment
    uint8_t brightness; // brightness of Led Segment
};






} // namespace Led

#endif // !LED_H