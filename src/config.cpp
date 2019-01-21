#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "config.h"

config_t config; // initiate the config structure

bool readSettings(void)
{

    const char *filename = "/globals.txt";
    File file = SD.open(filename);

    // Use arduinojson.org/assistant to compute the capacity.
    size_t capacity = JSON_OBJECT_SIZE(2) + 40;
    DynamicJsonBuffer jsonBuffer(capacity);


    // Parse the root object
    JsonObject &root = jsonBuffer.parseObject(file);

    if (!root.success())
    {
        Serial.println(F("Failed to read GlobalSettings.txt"));
    }

    else
    {
        // Copy values from the JsonObject to the Config
        config.globalSettings.currentBank = root["currentBank"];
        config.globalSettings.brightness = root["brightness"];

        // Close the file (File's destructor doesn't close the file)
        file.close();

        Serial.print("Reading Settings:\n\n");
        Serial.print("Current Bank: ");
        Serial.print(config.globalSettings.currentBank);
        Serial.print("\nBrightness:   ");
        Serial.print(config.globalSettings.brightness);
        Serial.print("\n");

        return true;
    }
}

bool writeSettings(void)
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
        Serial.println(F("Successfully wrote settings to file."));
    }

    // Close the file (File's destructor doesn't close the file)
    file.close();
}