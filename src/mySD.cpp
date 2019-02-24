#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "config.h"

const int chipSelect = BUILTIN_SDCARD;

struct Config2
{
    char hostname[64];
    int port;
};

const char *filename = "/bank.txt"; // <- SD library uses 8.3 filenames
Config2 config2;

// Loads the configuration from a file
void loadConfiguration(const char *filename, Config2 &config)
{
    File file = SD.open(filename);

    StaticJsonBuffer<512> jsonBuffer;

    // Parse the root object
    JsonObject &root = jsonBuffer.parseObject(file);

    if (!root.success())
        Serial.println(F("Failed to read file, using default configuration"));

    // Copy values from the JsonObject to the Config
    config.port = root["port"] | 2731;
    strlcpy(config.hostname,                  // <- destination
            root["hostname"] | "example.com", // <- source
            sizeof(config.hostname));         // <- destination's capacity

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config2 &config2)
{
    // Delete existing file, otherwise the configuration is appended to the file
    SD.remove(filename);

    // Open file for writing
    File file = SD.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("Failed to create file"));
        return;
    }

    // Allocate the memory pool on the stack
    // Don't forget to change the capacity to match your JSON document.
    // Use https://arduinojson.org/assistant/ to compute the capacity.
    StaticJsonBuffer<256> jsonBuffer;

    // Parse the root object
    JsonObject &root = jsonBuffer.createObject();

    // Set the values
    root["hostname"] = config2.hostname;
    root["port"] = config2.port;

    // Serialize JSON to file
    if (root.printTo(file) == 0)
    {
        Serial.println(F("Failed to write to file"));
    }

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

// Prints the content of a file to the Serial
void printFile(const char *filename)
{
    // Open file for reading
    File file = SD.open("/bank.txt");
    if (!file)
    {
        Serial.println(F("Failed to read file"));
        return;
    }

    // Extract each characters by one by one
    while (file.available())
    {
        Serial.print((char)file.read());
    }
    Serial.println();

    // Close the file (File's destructor doesn't close the file)
    file.close();
}

void initSD(void)
{

    Serial.begin(9600);
    delay(2000);

    // Initialize SD library
    while (!SD.begin(chipSelect))
    {
        Serial.println("Failed to initialize SD library Is The Card Inserted?");
        delay(1000);
    }

    readSettings();
    
    // writeSettings();

    printSettings();

   printFile("/bank00.txt");

    

  //  // Should load default config if run for the first time
  //  Serial.println(F("Loading configuration..."));
  //  loadConfiguration(filename, config);
//
  //  // Create configuration file
  //  Serial.println(F("Saving configuration..."));
  //  saveConfiguration(filename, config);
//
  //  // Dump config file
  //  Serial.println(F("Print config file..."));
  //  printFile(filename);
}
