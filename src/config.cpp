#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "config.h"
#include <stdlib.h>

config_t config; // initiate the config structure

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       readGlobals                                                          //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readGlobals(void)
{
    const char *filename = "/globals.txt";
    File file = SD.open(filename);

    size_t capacity = JSON_OBJECT_SIZE(2) + 40;
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.parseObject(file);

    if (!root.success()) // file not found, so create new one from Defaults
    {
        Serial.print("Global Settings File does not exist. \nusing default configuration.\n");

        // define default Values
        config.globalSettings.currentBank = 1;
        config.globalSettings.brightness = 100;
        config.globalSettings.midiChannel = 1;

        writeGlobals();
        Serial.print("\n");
    }

    else // File found
    {
        // Copy values from the JsonObject to the Config
        config.globalSettings.currentBank = root["currentBank"];
        config.globalSettings.brightness = root["brightness"];
        config.globalSettings.midiChannel = root["midiChannel"];

        // Close the file (File's destructor doesn't close the file)
        file.close();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         readBank                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readBank(uint8_t bankNr)
{
    char filename[] = "/bank00.txt";

    filename[5] = bankNr / 10 + '0';
    filename[6] = bankNr % 10 + '0';

    // const char *filename = "/bank1.txt";
    File file = SD.open(filename);

    size_t capacity = 16 * JSON_ARRAY_SIZE(2) + 16 * JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2);
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.parseObject(file);

    if (!root.success()) // file not found
    {
        if (bankNr != 0) // its not the Default, so use Values From default to create new bank
        {
            Serial.print("Bank Nr. ");
            Serial.print(bankNr);
            Serial.println(" does not exist, using Values from Default bank File.");
            readBank(00);      // get the values from the existing Default File
            writeBank(bankNr); // write these into the asked Bank File
        }

        else // the default File does not exist, so create it from scratch
        {
            Serial.println("Default Bank File does not exist eighter.");
            Serial.print("Creating new Default Bank File.\n\n");

            // Define Default Values

            config.settings.TrackColor[0] = RED;
            config.settings.TrackColor[1] = BLUE;
            config.settings.TrackColor[2] = GREEN;
            config.settings.TrackColor[3] = ORANGE;
            config.settings.TrackColor[4] = VIOLET;

            config.settings.function[0].midi_CC = 1;
            config.settings.function[0].function = Track_Start_Stop;
            config.settings.function[0].additionalParameter[0] = 0;
            config.settings.function[0].additionalParameter[1] = 0;

            config.settings.function[1].midi_CC = 2;
            config.settings.function[1].function = Track_Play_Rec;
            config.settings.function[1].additionalParameter[0] = 0;
            config.settings.function[1].additionalParameter[1] = 0;

            config.settings.function[2].midi_CC = 3;
            config.settings.function[2].function = Track_Start_Stop;
            config.settings.function[2].additionalParameter[0] = 0;
            config.settings.function[2].additionalParameter[1] = 0;

            config.settings.function[3].midi_CC = 4;
            config.settings.function[3].function = Track_Play_Rec;
            config.settings.function[3].additionalParameter[0] = 0;
            config.settings.function[3].additionalParameter[1] = 0;

            config.settings.function[4].midi_CC = 5;
            config.settings.function[4].function = Track_Start_Stop;
            config.settings.function[4].additionalParameter[0] = 0;
            config.settings.function[4].additionalParameter[1] = 0;

            config.settings.function[5].midi_CC = 6;
            config.settings.function[5].function = Track_Play_Rec;
            config.settings.function[5].additionalParameter[0] = 0;
            config.settings.function[5].additionalParameter[1] = 0;

            config.settings.function[6].midi_CC = 7;
            config.settings.function[6].function = Track_Start_Stop;
            config.settings.function[6].additionalParameter[0] = 0;
            config.settings.function[6].additionalParameter[1] = 0;

            config.settings.function[7].midi_CC = 8;
            config.settings.function[7].function = Track_Play_Rec;
            config.settings.function[7].additionalParameter[0] = 0;
            config.settings.function[7].additionalParameter[1] = 0;

            config.settings.function[8].midi_CC = 9;
            config.settings.function[8].function = Track_Start_Stop;
            config.settings.function[8].additionalParameter[0] = 0;
            config.settings.function[8].additionalParameter[1] = 0;

            config.settings.function[9].midi_CC = 10;
            config.settings.function[9].function = Track_Play_Rec;
            config.settings.function[9].additionalParameter[0] = 0;
            config.settings.function[9].additionalParameter[1] = 0;

            config.settings.function[10].midi_CC = 11;
            config.settings.function[10].function = All_Start_Stop;
            config.settings.function[10].additionalParameter[0] = 0;
            config.settings.function[10].additionalParameter[1] = 0;

            config.settings.function[11].midi_CC = 12;
            config.settings.function[11].function = Last_Undo_Redo;
            config.settings.function[11].additionalParameter[0] = 0;
            config.settings.function[11].additionalParameter[1] = 0;

            config.settings.function[12].midi_CC = 13;
            config.settings.function[12].function = Tap_Tempo;
            config.settings.function[12].additionalParameter[0] = 0;
            config.settings.function[12].additionalParameter[1] = 127;

            config.settings.function[13].midi_CC = 14;
            config.settings.function[13].function = Rhythm_Level;
            config.settings.function[13].additionalParameter[0] = 0;
            config.settings.function[13].additionalParameter[1] = 0;

            config.settings.function[14].midi_CC = 15;
            config.settings.function[14].function = Mic_Mute;
            config.settings.function[14].additionalParameter[0] = 0;
            config.settings.function[14].additionalParameter[1] = 0;

            config.settings.function[15].midi_CC = 16;
            config.settings.function[15].function = Input_FX_Inc_Dec;
            config.settings.function[15].additionalParameter[0] = 0;
            config.settings.function[15].additionalParameter[1] = 0;

            writeBank(0);      // use these defaults to write the Default File
        }
    }

    else // specified file found and readable
    {
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

            case Mic_Mute:
                config.settings.function[i].function = Mic_Mute;
                break;

            case Target_Track_Inc:
                config.settings.function[i].function = Target_Track_Inc;
                break;

            case Target_Track_Dec:
                config.settings.function[i].function = Target_Track_Dec;
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
        Serial.print("Loaded Bank Nr. ");
        Serial.println(bankNr);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                        writeGlobals                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void writeGlobals(void)
{
    char *filename = "/globals.txt";
    // Delete existing file, otherwise the configuration is appended to the file
    SD.remove(filename);

    // Open file for writing
    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to create file");
    }

    size_t capacity = JSON_OBJECT_SIZE(2) + 40;
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.createObject();

    root["currentBank"] = config.globalSettings.currentBank;
    root["brightness"] = config.globalSettings.brightness;
    root["midiChannel"] = config.globalSettings.midiChannel;

    // Serialize JSON to file
    if (root.printTo(file) == 0)
    {
        Serial.println("Failed to write to Global Settings file");
    }
    else
    {
        Serial.println("Successfully wrote Global Settings to file.");
    }

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          writeBank                                                         //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void writeBank(uint8_t bankNr)
{

    char filename[] = "/bank00.txt";

    filename[5] = bankNr / 10 + '0';
    filename[6] = bankNr % 10 + '0';

    // char *filename = "/bank1.txt";
    // Delete existing file, otherwise the configuration is appended to the file
    SD.remove(filename);

    // Open file for writing
    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to create file");
    }

    size_t capacity = 16 * JSON_ARRAY_SIZE(2) + 16 * JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(5) + JSON_ARRAY_SIZE(16) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2);
    DynamicJsonBuffer jsonBuffer(capacity);

    JsonObject &root = jsonBuffer.createObject();

    JsonObject &bankSettings = root.createNestedObject("bankSettings");

    JsonArray &bankSettings_TrackColors = bankSettings.createNestedArray("TrackColors");
    for (int i = 0; i < 5; i++)
    {
        bankSettings_TrackColors.add((int)config.settings.TrackColor[i]);
    }

    JsonArray &bankSettings_buttons = bankSettings.createNestedArray("buttons");

    for (int i = 0; i < 16; i++)
    {
        JsonArray &bankSettings_current_button = bankSettings_buttons.createNestedArray();
        bankSettings_current_button.add((int)config.settings.function[i].midi_CC);
        bankSettings_current_button.add((int)config.settings.function[i].function);
        JsonArray &bankSettings_current_button_Adititional_Settings = bankSettings_current_button.createNestedArray();
        bankSettings_current_button_Adititional_Settings.add((int)config.settings.function[i].additionalParameter[0]);
        bankSettings_current_button_Adititional_Settings.add((int)config.settings.function[i].additionalParameter[1]);
    }

    // Serialize JSON to file
    if (root.printTo(file) == 0)
    {
        Serial.print("Failed to write to bank Nr.");
        Serial.print(bankNr);
        Serial.print(".\n");
        // return false;
    }
    else
    {
        if (bankNr == 0)
        {
            Serial.println("Successfully wrote Settings to default Bank File.");
        }
        else
        {
            Serial.print("Successfully wrote Settings for Bank Nr. ");
            Serial.println(bankNr);
        }
        // return true;
    }

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       printSettings                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printSettings(void)
{
    // Globals
    Serial.print("\n\n\nReading Settings:\n\n");
    Serial.print("Current Bank:            ");
    Serial.println(config.globalSettings.currentBank);
    Serial.print("Brightness:              ");
    Serial.println(config.globalSettings.brightness);
    Serial.print("Midi Channel:            ");
    Serial.println(config.globalSettings.midiChannel);

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
            Serial.println("Violet");
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

        case Mic_Mute:
            Serial.println("Mute Microphone");
            break;

        case Target_Track_Inc:
            Serial.println("Increase Target Track");
            break;

        case Target_Track_Dec:
            Serial.println("Decrease Target Track");
            break;

        default:
            Serial.println("Not assigned");
            break;
        }
        Serial.print("Additional Parameter 1:  ");
        Serial.println(config.settings.function[i].additionalParameter[0]);
        Serial.print("Additional Parameter 2:  ");
        Serial.println(config.settings.function[i].additionalParameter[0]);
        Serial.print("\n\n");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                        readSettings                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readSettings(void)
{
    readGlobals();

    readBank(config.globalSettings.currentBank);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                       writeSettings                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void writeSettings(void)
{
   writeGlobals();

   writeBank(config.globalSettings.currentBank);
}