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
}

bool readBank(uint8_t bankNr)
{
    const char *filename = "/bank.txt";
    File file = SD.open(filename);

    size_t capacity = 16 * JSON_ARRAY_SIZE(2) + 16 * JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2);
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

        JsonArray &bankSettings_buttons = root["bankSettings"]["buttons"];

        for (int i = 0; i < 16; i++)
        {
            JsonArray &bankSettings_current_button = bankSettings_buttons[i];

            config.settings.function[i].midi_CC = bankSettings_current_button[0];

            switch (bankSettings_current_button.get<int>(1))
            {
            case Target_Track_Start_Stop:
                config.settings.function[i].function = Target_Track_Start_Stop;
                break;

            case Target_Track_Stop:
                config.settings.function[i].function = Target_Track_Stop;
                break;

            case Target_Track_Clear:
                config.settings.function[i].function = Target_Track_Clear;
                break;

            case Target_Track_Undo_redo:
                config.settings.function[i].function = Target_Track_Undo_redo;
                break;

            case Target_Track_Play_Level:
                config.settings.function[i].function = Target_Track_Play_Level;
                break;

            case All_Start_Stop:
                config.settings.function[i].function = All_Start_Stop;
                break;

            case Last_Undo_Redo:
                config.settings.function[i].function = Last_Undo_Redo;
                break;

            case Tap_Tempo:
                config.settings.function[i].function = Tap_Tempo;
                break;

            case Bank_Up_Down:
                config.settings.function[i].function = Bank_Up_Down;
                break;

            case Track_Start_Stop:
                config.settings.function[i].function = Track_Start_Stop;
                break;

            case Track_Play_Rec:
                config.settings.function[i].function = Track_Play_Rec;
                break;

            case Track_Clear:
                config.settings.function[i].function = Track_Clear;
                break;

            case Track_Undo_Redo:
                config.settings.function[i].function = Track_Undo_Redo;
                break;

            case Track_Pan:
                config.settings.function[i].function = Track_Pan;
                break;

            case All_Clear:
                config.settings.function[i].function = All_Clear;
                break;

            case Rhythm_Level:
                config.settings.function[i].function = Rhythm_Level;
                break;

            case Rhythm_Pattern:
                config.settings.function[i].function = Memory_Level;
                break;

            case Memory_Level:
                config.settings.function[i].function = Memory_Level;
                break;

            case Master_Comp:
                config.settings.function[i].function = Master_Comp;
                break;

            case Master_Reverb:
                config.settings.function[i].function = Master_Reverb;
                break;

            case Overdub_Mode:
                config.settings.function[i].function = Overdub_Mode;
                break;

            case Input_FX_On_Off:
                config.settings.function[i].function = Input_FX_On_Off;
                break;

            case Input_FX_Inc_Dec:
                config.settings.function[i].function = Input_FX_Inc_Dec;
                break;

            case Track_FX_On_Off:
                config.settings.function[i].function = Track_FX_On_Off;
                break;

            case Track_FX_Inc_Dec:
                config.settings.function[i].function = Track_FX_Inc_Dec;
                break;

            case Target_Track_Inc_Dec:
                config.settings.function[i].function = Target_Track_Inc_Dec;
                break;

            default:
                config.settings.function[i].function = BLANK;
                break;
            }

            config.settings.function[i].additionalParameter[0] = bankSettings_current_button[2][0];
            config.settings.function[i].additionalParameter[1] = bankSettings_current_button[2][1];
        }

        // Close the file (File's destructor doesn't close the file)
        file.close();

        return true;
    }
}

void printSettings(void)
{
    // Globals
    Serial.print("\n\n\nReading Settings:\n\n");
    Serial.print("Current Bank:            ");
    Serial.println(config.globalSettings.currentBank);
    Serial.print("Brightness:              ");
    Serial.println(config.globalSettings.brightness);

    Serial.println("\nTrack Colors");
    for (int i = 0; i < 5; i++)
    {
        Serial.print("Track Nr.");
        Serial.print(i + 1);
        Serial.print(":              ");
        switch (config.settings.TrackColor[i])
        {
        case RED:
            Serial.println("Red");
            break;

        case GREEN:
            Serial.println("Green");
            break;

        case BLUE:
            Serial.println("Blue");
            break;

        case WHITE:
            Serial.println("White");
            break;

        case BLACK:
            Serial.println("Black");
            break;

        case YELLOW:
            Serial.println("Yellow");
            break;

        case ORANGE:
            Serial.println("Orange");
            break;

        case VIOLET:
            Serial.println("VIOLET");
            break;

        default:
            Serial.println("Not specified");
            break;
        }
    }
    Serial.print("\n\n");

    for (int i = 0; i < 16; i++)
    {
        Serial.print("Button Nr.");
        Serial.print(i + 1);
        Serial.print(":\n");
        Serial.print("Midi CC:                 ");
        Serial.println(config.settings.function[i].midi_CC);
        Serial.print("Function:                ");

        switch (config.settings.function[i].function)
        {
        case Target_Track_Start_Stop:
            Serial.println("Target Track Start/Stop");
            break;

        case Target_Track_Stop:
            Serial.println("Target Track Stop");
            break;

        case Target_Track_Clear:
            Serial.println("Target Track Clear");
            break;

        case Target_Track_Undo_redo:
            Serial.println("Target Track Undo/Redo");
            break;

        case Target_Track_Play_Level:
            Serial.println("Target Track Play Level");
            break;

        case All_Start_Stop:
            Serial.println("All Start/Stop");
            break;

        case Last_Undo_Redo:
            Serial.println("Last Undo/Redo");
            break;

        case Tap_Tempo:
            Serial.println("Tap Tempo");
            break;

        case Bank_Up_Down:
            Serial.println("Bank Up/Down");
            break;

        case Track_Start_Stop:
            Serial.println("Track Start/Stop");
            break;

        case Track_Play_Rec:
            Serial.println("Track Play/Record");
            break;

        case Track_Clear:
            Serial.println("Track Clear");
            break;

        case Track_Undo_Redo:
            Serial.println("Track Undo/Redo");
            break;

        case Track_Pan:
            Serial.println("Track Pan");
            break;

        case All_Clear:
            Serial.println("All Clear");
            break;

        case Rhythm_Level:
            Serial.println("Rhythm Level");
            break;

        case Rhythm_Pattern:
            Serial.println("Rhythm Pattern");
            break;

        case Memory_Level:
            Serial.println("Memory Level");
            break;

        case Master_Comp:
            Serial.println("Master Compressor");
            break;

        case Master_Reverb:
            Serial.println("Master Reverb");
            break;

        case Overdub_Mode:
            Serial.println("Overdub Mode");
            break;

        case Input_FX_On_Off:
            Serial.println("Input Effects On/Off");
            break;

        case Input_FX_Inc_Dec:
            Serial.println("Input Effects Increase/Decrease");
            break;

        case Track_FX_On_Off:
            Serial.println("Track Effects On/Off");
            break;

        case Track_FX_Inc_Dec:
            Serial.println("Track Effects Increase/Decrease");
            break;

        case Target_Track_Inc_Dec:
            Serial.println("Target Track Increase/Decrease");
            break;

        default:
            Serial.println("Not assigned");
            break;
        }
        Serial.print("Additional Parameter 1:  ");
        Serial.println(config.settings.function[i].additionalParameter[0]);
        Serial.print("Additional Parameter 1:  ");
        Serial.println(config.settings.function[i].additionalParameter[0]);
        Serial.print("\n\n");
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
        Serial.println("Failed to create file");
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
        Serial.println("Failed to write to file");
    }
    else
    {
        Serial.println("Successfully wrote global Settings to file.");
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
        Serial.println("Failed to create file");
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