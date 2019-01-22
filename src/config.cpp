#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "config.h"

config_t config; // initiate the config structure

bool readGlobals(void)
{

    const char *filename = "/globals.txt";
    File file = SD.open(filename);

    size_t capacity = JSON_OBJECT_SIZE(2) + 40;
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.parseObject(file);

    if (!root.success())
    {
        Serial.println(F("Failed to read GlobalSettings.txt using default configuration"));
    }

    // Copy values from the JsonObject to the Config
    config.globalSettings.currentBank = root["currentBank"] | 1;
    config.globalSettings.brightness = root["brightness"] | 100;

    // Close the file (File's destructor doesn't close the file)
    file.close();

    Serial.print("Reading Settings:\n\n");
    Serial.print("Current Bank: ");
    Serial.print(config.globalSettings.currentBank);
    Serial.print("\nBrightness:   ");
    Serial.print(config.globalSettings.brightness);
    Serial.print("\n");
}

bool readBank(uint8_t bankNr)
{

    const char *filename = "/bank.txt";
    File file = SD.open(filename);

    size_t capacity = JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(1) + 10 * JSON_OBJECT_SIZE(2) + 6 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6);
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.parseObject(file);

    if (!root.success())
    {
        Serial.println("Failed to read bank.txt using default configuration");
    }

    else
    {
        // Copy values from the JsonObject to the Config
        JsonArray &bankSettings_TrackColors = root["bankSettings"]["TrackColors"];

        // get Colors for tracks from array and store in RAM
        for (int i = 0; i < 5; i++)
        {
            switch (bankSettings_TrackColors.get<int>(i))
            {
            case 0:
                config.settings.TrackColor[i] = RED;
                break;
            case 1:
                config.settings.TrackColor[i] = GREEN;
                break;
            case 2:
                config.settings.TrackColor[i] = BLUE;
                break;
            case 3:
                config.settings.TrackColor[i] = WHITE;
                break;
            case 4:
                config.settings.TrackColor[i] = BLACK;
                break;
            case 5:
                config.settings.TrackColor[i] = YELLOW;
                break;
            case 6:
                config.settings.TrackColor[i] = ORANGE;
                break;
            case 7:
                config.settings.TrackColor[i] = VIOLET;
                break;

            default:
                config.settings.TrackColor[i] = WHITE;
                break;
            }
        }

        // Close the file (File's destructor doesn't close the file)
        file.close();

        Serial.print("Track Colors:\n\n");
        for (int i = 0; i < 5; i++)
        {
            Serial.print("Track ");
            Serial.print(i + 1);
            Serial.print(":    ");
            Serial.println(config.settings.TrackColor[i]);
        }
        return true;
    }
}

bool readSettings(void)
{

    bool result1, result2;

    result1 = readGlobals();

    result2 = readBank(1);

    if (result1 == true && result2 == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool writeGlobals(void)
{
    char *filename = "/globals.txt";
    // Delete existing file, otherwise the configuration is appended to the file
    SD.remove(filename);

    // Open file for writing
    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return false;
    }

    size_t capacity = JSON_OBJECT_SIZE(2) + 40;
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.createObject();

    root["currentBank"] = config.globalSettings.currentBank;
    root["brightness"] = config.globalSettings.brightness;

    // Serialize JSON to file
    if (root.printTo(file) == 0)
    {
        Serial.println(F("Failed to write to file"));
    }
    else
    {
        Serial.println(F("Successfully wrote global Settings to file."));
    }

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

bool writeBank(uint8_t bankNr)
{
    char *filename = "/bank.txt";
    // Delete existing file, otherwise the configuration is appended to the file
    SD.remove(filename);

    // Open file for writing
    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return false;
    }

    size_t capacity = JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(1) + 10 * JSON_OBJECT_SIZE(2) + 6 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6);
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.createObject();

    JsonObject &bankSettings = root.createNestedObject("bankSettings");
    // bankSettings["trackOneColor"] = config.settings.track_One_color;
    // bankSettings["trackTwoColor"] = config.settings.track_Two_color;
    // bankSettings["trackTreeColor"] = config.settings.track_Three_color;
    // bankSettings["trackFourColor"] = config.settings.track_Four_color;
    // bankSettings["trackFiveColour"] = config.settings.track_Five_color;

    JsonArray &bankSettings_buttons = bankSettings.createNestedArray("buttons");

    JsonObject &bankSettings_buttons_0 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_0["CC_Nr"] = config.settings.function[0].midi_CC;
    bankSettings_buttons_0["Function"] = "Play/Overdub";

    JsonObject &bankSettings_buttons_1 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_1["CC_Nr"] = 2;
    bankSettings_buttons_1["Function"] = "Start/Stop";
    bankSettings_buttons_1["PlayMode"] = "multi";

    JsonObject &bankSettings_buttons_2 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_2["CC_Nr"] = 3;
    bankSettings_buttons_2["Function"] = "Play/Overdub";
    bankSettings_buttons_2["OnStart"] = "Play";

    JsonObject &bankSettings_buttons_3 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_3["CC_Nr"] = 4;
    bankSettings_buttons_3["Function"] = "Start/Stop";

    JsonObject &bankSettings_buttons_4 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_4["CC_Nr"] = 5;
    bankSettings_buttons_4["Function"] = "Play/Overdub";
    bankSettings_buttons_4["OnStart"] = "Overdub";

    JsonObject &bankSettings_buttons_5 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_5["CC_Nr"] = 6;
    bankSettings_buttons_5["Function"] = "Start/Stop";

    JsonObject &bankSettings_buttons_6 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_6["CC_Nr"] = 7;
    bankSettings_buttons_6["Function"] = "Play/Overdub";
    bankSettings_buttons_6["OnStart"] = "Play";

    JsonObject &bankSettings_buttons_7 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_7["CC_Nr"] = 8;
    bankSettings_buttons_7["Function"] = "Start/Stop";

    JsonObject &bankSettings_buttons_8 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_8["CC_Nr"] = 9;
    bankSettings_buttons_8["Function"] = "Play/Overdub";
    bankSettings_buttons_8["OnStart"] = "Overdub";

    JsonObject &bankSettings_buttons_9 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_9["CC_Nr"] = 10;
    bankSettings_buttons_9["Function"] = "Start/Stop";

    JsonObject &bankSettings_buttons_10 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_10["CC_Nr"] = 11;
    bankSettings_buttons_10["Function"] = "AllStart";

    JsonObject &bankSettings_buttons_11 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_11["CC_Nr"] = 12;
    bankSettings_buttons_11["Function"] = "Undo/Redo";

    JsonObject &bankSettings_buttons_12 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_12["CC_Nr"] = 13;
    bankSettings_buttons_12["Function"] = "TapTempo";

    JsonObject &bankSettings_buttons_13 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_13["CC_Nr"] = 14;
    bankSettings_buttons_13["Function"] = "Blank";

    JsonObject &bankSettings_buttons_14 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_14["CC_Nr"] = 15;
    bankSettings_buttons_14["Function"] = "MicMute";

    JsonObject &bankSettings_buttons_15 = bankSettings_buttons.createNestedObject();
    bankSettings_buttons_15["CC_Nr"] = 16;
    bankSettings_buttons_15["Function"] = "Pan";

    Serial.println(" json created");

    // Serialize JSON to file
    if (root.printTo(file) == 0)
    {
        Serial.println("Failed to write to bank File");
    }
    else
    {
        Serial.println("Successfully wrote Bank Settings to file.");
    }

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

bool writeSettings(void)
{
    bool result1, result2;

    result1 = writeGlobals();

    result2 = writeBank(1);

    if (result1 == true && result2 == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}