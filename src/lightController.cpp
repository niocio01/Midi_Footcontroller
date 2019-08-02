#include "lightController.h"
#include "functionHandler.h"
#include "configEditor.h"
#include "arduino.h"
#include "led.h"

namespace ButtonLights
{

Led::Segment segmentLights[6];

void init(void)
{

    for (int i = 0; i < 6; i++)
    {
        segmentLights[i].setStart((8 * i));
        segmentLights[i].setEnd(8 * (i + 1) - 1);
    }

    for (int j = 0; j < 6; j++)
    {
        Serial.print("Segment ");
        Serial.print(j);
        Serial.print(" Start: ");
        Serial.print(segmentLights[j].getStart());
        Serial.print(" End: ");
        Serial.println(segmentLights[j].getEnd());
    }

    // segmentLights[0].setAll(RGBW_YELLOW);
    // segmentLights[1].setAll(RGBW_GREEN);
    // segmentLights[2].setAll(RGBW_BLUE);
    // segmentLights[3].setAll(RGBW_WHITE);
    // segmentLights[4].setAll(RGBW_YELLOW);
    // segmentLights[5].setAll(RGBW_ORANGE);

    Led::update();

    Serial.println("initdone");
}

void setTrackLight(uint8_t track, ButtonLights::trackLight_t type)
{
    int color = getColorCode(getTrackColor(track - 1));
    Serial.print("setting Track Nr. ");
    Serial.print(track);
    Serial.print(" to color: 0x");
    Serial.println(color, HEX);

    switch (type)
    {
    case EMPTY:

        segmentLights[(track - 1) * 2].setBrightness(25);
        segmentLights[((track - 1) * 2) + 1].setBrightness(25);

        segmentLights[(track - 1) * 2].setAll(color);
        segmentLights[((track - 1) * 2) + 1].setAll(color);

        break;

    case PAUSED:

        segmentLights[(track - 1) * 2].setBrightness(80);
        segmentLights[((track - 1) * 2) + 1].setBrightness(80);

        segmentLights[(track - 1) * 2].setAll(color);
        segmentLights[((track - 1) * 2) + 1].setAll(color);

        break;

    default:
        break;
    }
    Led::update();
}

void updateButtonLights(void)
{
}

} // namespace ButtonLights