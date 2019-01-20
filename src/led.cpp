#include <Adafruit_NeoPixel.h>

#define PIN 20
#define NUMPIXELS 5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void initLed(void)
{

    pixels.begin(); // This initializes the NeoPixel library.
}

void ledTest(void)
{

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(150, 0, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = NUMPIXELS; i >= 0 ; i--)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 150, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = NUMPIXELS; i >= 0 ; i--)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 150, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = NUMPIXELS; i >= 0 ; i--)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 150)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }

    for (int i = NUMPIXELS; i >= 0 ; i--)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0, 0)); // Moderately bright green color.

        pixels.show(); // This sends the updated pixel color to the hardware.

        delay(500); // Delay for a period of time (in milliseconds).
    }
}