#ifndef LED_H
#define LED_H

// create namespace to avoid name reusing
namespace Led 
{

const int numLed = 5;
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
#define RGBW_CODE_RED 0x00FF0000
#define RGBW_CODE_GREEN 0x0000FF00
#define RGBW_CODE_BLUE 0x000000FF
#define RGBW_CODE_YELLOW 0x00FFFF00
#define RGBW_CODE_PINK 0x00FF1088
#define RGBW_CODE_ORANGE 0x00E05800
#define RGBW_CODE_WHITE 0xFF000000

// non class functions

// initiate the Led Strip
void init(void);

// send current frambuffer to leds
void update(void);

// set Brightness multiplier for all Leds
void setMasterBrightness(uint8_t newBrightness);

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
    Segment(uint8_t newStart, u_int8_t newEnd);

    // Overload Constructor
    Segment(uint8_t newStart, u_int8_t newEnd, uint8_t newBrightness);

// set functions

    // set start id for Led Segment
    void setStart(uint8_t newStart);

    // set end id for Led Segment
    void setEnd(uint8_t newEnd);

    // set Brightness for Led Segment
    void setBrightness(uint8_t newBrightness);

// get functions

    // get start id for Led Segment
    uint8_t getStart() const;

    // get end id for Led Segment
    uint8_t getEnd() const;

    // get Brightness of Led Segment
    uint8_t getBrightness() const;

private:
    uint8_t start;      // start id of Led Segment
    uint8_t end;        // end id of Led Segment
    uint8_t brightness; // brightness of Led Segment
};
} // namespace Led

#endif // !LED_H