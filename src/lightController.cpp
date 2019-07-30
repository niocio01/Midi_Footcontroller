#include "lightController.h"
#include "functionHandler.h"
#include "configEditor.h"
#include "arduino.h"
#include "led.h"



namespace ButtonLights
{

 

void init(void)
{

   Led::Segment segmentLights[6];

    for (int i = 0; i < 6; i++)
    {
        segmentLights[i].setStart((8 * i));
        segmentLights[i].setEnd(8 * (i + 1)-1);
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

    segmentLights[0].setStart(30);
    segmentLights[0].setEnd(35);

    segmentLights[0].setAll(RGBW_YELLOW);
    //segmentLights[1].setAll(RGBW_GREEN);
    //segmentLights[2].setAll(RGBW_BLUE);
    //segmentLights[3].setAll(RGBW_WHITE);
    //segmentLights[4].setAll(RGBW_YELLOW);
    //segmentLights[5].setAll(RGBW_ORANGE);
    

    Serial.println("initdone");

    for (int j = 0; j < 6; j++)
    {
        Serial.print("Segment ");
        Serial.print(j);
        Serial.print(" Start: ");
        Serial.print(segmentLights[j].getStart());
        Serial.print(" End: ");
        Serial.println(segmentLights[j].getEnd());
    }
}

void setTrackLight(uint8_t track, ButtonLights::trackLight_t type)
{
    int color = getColorCode(getTrackColor(track - 1));
    Serial.print(color);

    switch (type)
    {
    case EMPTY:

        Serial.println(track);
        //setButtonBrightness(track * 2 - 2, 100);
        //setButtonBrightness(track * 2 - 1, 100);

        //segmentLights[track * 2 - 2].setAll(color);
        //segmentLights[track * 2 - 1].setAll(color);
        // setButtonColor(track * 2 - 2, color);
        // setButtonColor(track * 2 - 1, color);



        break;

    default:
        delay(10);
        break;
    }
}

void updateButtonLights(void)
{
}

} // namespace ButtonLights