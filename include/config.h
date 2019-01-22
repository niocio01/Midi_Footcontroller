#ifndef CONFIG_H
#define CONFIG_H 

#include <Arduino.h>
#include "led.h"


typedef enum // all the possible Function Types get united
{
    BLANK,
    Target_Track_Start_Stop,
    Target_Track_Stop,
    Target_Track_Clear,
    Target_Track_Undo_redo,
    Target_Track_Play_Level,
    All_Start_Stop,
    Last_Undo_Redo,
    Tap_Tempo,
    Bank_Up_Down,


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
    Mic_Mute,

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

} globalSettings_t;


typedef struct // master Struct Of current Config
{
    globalSettings_t globalSettings;
    bankSettings_t settings;

} config_t;

///////////////////////////////////////////////////////////////////////////////////



bool readGlobals(void);

bool readBank(uint8_t bankNr);

bool readSettings(void);



bool writeGlobals(void);

bool writeBank(uint8_t bankNr);

bool writeSettings(void);


void printSettings(void);

#endif // !CONFIG_H