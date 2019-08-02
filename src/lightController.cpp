#include "lightController.h"
#include "functionHandler.h"
#include "configEditor.h"
#include "arduino.h"
#include "led.h"
#include "timedTasks.h"

namespace ButtonLights
{

Led::Segment segmentLights[6];

trackState_t trackState[3] = {};
trackState_t OldTrackState[3] = {};

bool blinkingState[3] = {false};

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

void setTrackState(uint8_t track, trackState_t state)
{
    trackState[track] = state;

    if (state == WAITING)
    {
        blinkingState[track] = true;
        TimedTasks::resetTask1();
    }
    else
    {
        ButtonLights::update();
    }
    
    
}

void update(void)
{

    for (int track = 0; track < 3; track++)
    {
        if (trackState[track] != OldTrackState[track] or trackState[track] == WAITING)
        {
            // Serial.print("Track ");
            // Serial.print(track);
            // Serial.print(": State ");
            // Serial.println(trackState[track]);


            int color = getColorCode(getTrackColor(track));

            switch (trackState[track])
            {
            case EMPTY:

                segmentLights[track * 2].setBrightness(25);
                segmentLights[track * 2 + 1].setBrightness(25);

                segmentLights[track * 2].setAll(color);
                segmentLights[track * 2 + 1].setAll(color);

                Serial.print("Setting Track ");
                Serial.print(track);
                Serial.print(" to Color 0x");
                Serial.println(color, HEX);

                break;

            case WAITING:

                if (blinkingState[track] == false)
                {
                    blinkingState[track] = true;
                    segmentLights[track * 2].setBrightness(50);
                    segmentLights[track * 2 + 1].setBrightness(50);

                    segmentLights[track * 2].setAll(color);
                    segmentLights[track * 2 + 1].setAll(color);
                }
                else
                {
                    blinkingState[track] = false;
                    segmentLights[track * 2].setBrightness(150);
                    segmentLights[track * 2 + 1].setBrightness(150);

                    segmentLights[track * 2].setAll(color);
                    segmentLights[track * 2 + 1].setAll(color);
                }
                break;

            default:
                Serial.print("Unimplemented light Update called (");
                Serial.print("Track ");
                Serial.print(track);
                Serial.print(" with state ");
                Serial.print(trackState[track]);
                Serial.println(")");
                break;
            }
        }
        OldTrackState[track] = trackState[track]; // update Old Buffer to current one
    }
    Led::update();
}

} // namespace ButtonLights