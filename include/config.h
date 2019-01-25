#ifndef CONFIG_H
#define CONFIG_H 

#include <Arduino.h>
#include "led.h"


typedef enum // all the possible Function Types get united
{
    Target_Track_Start_Stop = 1,
    Target_Track_Stop,
    Target_Track_Clear,
    Target_Track_Undo_redo,
    Target_Track_Play_Level,
    All_Start_Stop,
    Last_Undo_Redo,
    Tap_Tempo,
    Bank_Up_Down,

    // V1 Functions
    Track_Start_Stop,
    Track_Play_Rec,
    Track_Clear,
    Track_Undo_Redo,
    Track_Pan,
    All_Clear,
    Rhythm_Level,
    Rhythm_Pattern,
    Memory_Level,
    Master_Comp,
    Master_Reverb,
    Overdub_Mode,
    Input_FX_On_Off, // more options form RC-505 V1 avaiable
    Input_FX_Inc_Dec,
    Track_FX_On_Off,
    Track_FX_Inc_Dec,
    Target_Track_Inc_Dec,


    // Custom Functions
    Mic_Mute,
    Target_Track_Inc,
    Target_Track_Dec,
    BLANK = 0,

} Function_Type_t ;

typedef struct // every Button is Configured with a Midi CC and addiditional Settings for each function
{
    uint8_t midi_CC; // 1-31, 64-95
    Function_Type_t function;
    uint8_t additionalParameter[2];

} buttonFunction_t;


typedef struct
{
    RGB_Colors_t TrackColor[5];    
    buttonFunction_t function [16];

} bankSettings_t;


typedef struct
{
    uint8_t currentBank;
    uint8_t brightness;
    uint8_t midiChannel;

} globalSettings_t;


typedef struct // master Struct Of current Config
{
    globalSettings_t globalSettings;
    bankSettings_t settings;

} config_t;

///////////////////////////////////////////////////////////////////////////////////



void readGlobals(void);

void readBank(uint8_t bankNr);

void readSettings(void);



void writeGlobals(void);

void writeBank(uint8_t bankNr);

void writeSettings(void);


void printSettings(void);

#endif // !CONFIG_H