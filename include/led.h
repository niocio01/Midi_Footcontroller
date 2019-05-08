#ifndef LED_H
#define LED_H

typedef enum
{
    RED = 1,
    GREEN,
    BLUE,
    WHITE,
    BLACK,
    YELLOW,
    ORANGE,
    VIOLET,
} RGB_Colors_t;


#define this_RED    0x160000
#define this_GREEN  0x001600
#define this_BLUE   0x000016
#define this_YELLOW 0x101400
#define this_PINK   0x120009
#define this_ORANGE 0x100400
#define this_WHITE  0x101010


void initLed (void);

void ledTest(void);

void colorWipe(int color, int wait);

#endif // !LED_H