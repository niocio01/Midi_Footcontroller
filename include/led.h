#ifndef LED_H
#define LED_H

typedef enum
{
    RED,
    GREEN,
    BLUE,
    WHITE,
    BLACK,
    YELLOW,
    ORANGE,
    VIOLET,
} RGB_Colors_t;

void initLed (void);

void ledTest(void);

#endif // !LED_H