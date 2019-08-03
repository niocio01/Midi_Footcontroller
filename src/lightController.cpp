#include "lightController.h"
#include "functionHandler.h"
#include "configEditor.h"
#include "arduino.h"
#include "led.h"
#include "timedTasks.h"

namespace ButtonLights
{

const uint8_t LO = 25;
const uint8_t MI = 80;
const uint8_t HI = 255;

Led::Segment segmentLights[6];

trackState_t trackState[3] = {};
trackState_t OldTrackState[3] = {};

bool blinkingState[3] = {false};

uint8_t currentFrame[3] = {0, 0, 0};

uint8_t waitingForPausing[8][2][8] = {
    {{MI, LO, LO, LO, LO, LO, MI, HI}, {HI, MI, LO, LO, LO, LO, LO, LO}},
    {{LO, LO, LO, LO, LO, MI, HI, MI}, {MI, HI, MI, LO, LO, LO, LO, LO}},
    {{LO, LO, LO, LO, MI, HI, MI, LO}, {LO, MI, HI, MI, LO, LO, LO, LO}},
    {{LO, LO, LO, MI, HI, MI, LO, LO}, {LO, LO, MI, HI, MI, LO, LO, LO}},
    {{LO, LO, MI, HI, MI, LO, LO, LO}, {LO, LO, LO, MI, HI, MI, LO, LO}},
    {{LO, MI, HI, MI, LO, LO, LO, LO}, {LO, LO, LO, LO, MI, HI, MI, LO}},
    {{MI, HI, MI, LO, LO, LO, LO, LO}, {LO, LO, LO, LO, LO, MI, HI, MI}},
    {{HI, MI, LO, LO, LO, LO, LO, MI}, {MI, LO, LO, LO, LO, LO, MI, HI}}};

void init(void)
{

    for (int i = 0; i < 6; i++)
    {
        segmentLights[i].setStart((8 * i));
        segmentLights[i].setEnd(8 * (i + 1) - 1);
    }

    ButtonLights::setTrackState(0, ButtonLights::EMPTY);
    ButtonLights::setTrackState(1, ButtonLights::EMPTY);
    ButtonLights::setTrackState(2, ButtonLights::EMPTY);

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

    if (state == WAITING_FOR_PAUSING or state == WAITING_FOR_PLAYING or state == WAITING_FOR_RECORDING)
    {
        currentFrame[track] = 0; // start from the beginning
    }
    ButtonLights::update();
}

void update(void)
{

    for (int track = 0; track < 3; track++)
    {
        if (trackState[track] != OldTrackState[track])
        {
            int color = getColorCode(getTrackColor(track));

            Serial.print("\n Track  ");
            Serial.print(track);
            Serial.print(" Color: 0x ");
            Serial.print(color, HEX);

            switch (trackState[track])
            {
            case EMPTY:
                segmentLights[track * 2].setBrightness(LO);
                segmentLights[track * 2 + 1].setBrightness(LO);

                segmentLights[track * 2].setAll(color);
                segmentLights[track * 2 + 1].setAll(color);
                break;

            case PAUSED:
                segmentLights[track * 2].setBrightness(MI);
                segmentLights[track * 2 + 1].setBrightness(MI);

                segmentLights[track * 2].setAll(color);
                segmentLights[track * 2 + 1].setAll(color);
                break;

            case PLAYING:
                segmentLights[track * 2].setBrightness(HI);
                segmentLights[track * 2 + 1].setBrightness(MI);

                segmentLights[track * 2].setAll(color);
                segmentLights[track * 2 + 1].setAll(color);
                break;

            case RECORDING:
                segmentLights[track * 2].setBrightness(MI);
                segmentLights[track * 2 + 1].setBrightness(HI);

                segmentLights[track * 2].setAll(color);
                segmentLights[track * 2 + 1].setAll(color);
                break;

            case WAITING_FOR_PAUSING:
                // do nothing
                break;

            case WAITING_FOR_PLAYING:
                // do nothing
                break;

            case WAITING_FOR_RECORDING:
                // do nothing
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

void playAnimation(void)
{
    for (int track = 0; track < 3; track++) // go thru all tracks
    {
        // check, whether or not to play an animation for the current track
        if (trackState[track] == WAITING_FOR_PAUSING or trackState[track] == WAITING_FOR_PLAYING or trackState[track] == WAITING_FOR_RECORDING)
        {
            
            int color = getColorCode(getTrackColor(track)); // get the color
            Serial.print(track);
            Serial.print("  ");
            Serial.print(color, HEX);
            for (uint8_t pixel = 0; pixel < 8; pixel++) // go thur every Pixel
            {
                segmentLights[track * 2].setBrightness(waitingForPausing[currentFrame[track]][0][pixel]); // set the brightness
                segmentLights[track * 2].setLed(pixel, color);                                            // write the color to repace with the new brightness value

                segmentLights[track * 2 + 1].setBrightness(waitingForPausing[currentFrame[track]][1][pixel]); // set the brightness
                segmentLights[track * 2 + 1].setLed(pixel, color);                                            // write the color to repace with the new brightness value
            }
            // Serial.println();
        }
        if (currentFrame[track] == 7)
            currentFrame[track] = 0;
        else
            currentFrame[track]++;
    }
    Led::update(); // write all the data to the pixels
}

} // namespace ButtonLights