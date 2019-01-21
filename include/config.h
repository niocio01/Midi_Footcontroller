#ifndef CONFIG_H
#define CONFIG_H 

#include <Arduino.h>
#include "led.h"


// Individual Functions Structs with corresponding options

// -----------------------Target_Track_Start_Stop--------------------------------
typedef enum {
    SINGLE,
    MULTI,    
} Target_Track_Start_Stop_Modes_t;

typedef struct
{
    Target_Track_Start_Stop_Modes_t mode;
    
} Target_Track_Start_Stop_Options_t ;

// -----------------------------Target_Track_Stop---------------------------------
typedef struct
{

} Target_Track_Stop_Options_t;


// ------------------------------Target_Track_Clear--------------------------------
typedef struct
{

} Target_Track_Clear_Options_t;


// ---------------------------Target_Track_Undo_redo--------------------------------
typedef struct
{

} Target_Track_Undo_redo_Options_t;


// ----------------------------Target_Track_Play_Level--------------------------------
typedef struct
{

} Target_Track_Play_Level_Options_t;


// ------------------------------All_Start_Stop--------------------------------
typedef struct
{

} All_Start_Stop_Options_t;


// -----------------------------Last_Undo_Redo---------------------------------
typedef struct
{

} Last_Undo_Redo_Options_t;


// -----------------------------Tap_Tempo---------------------------------
typedef struct
{

} Tap_Tempo_Options_t;


// ------------------------------Bank_Up_Down--------------------------------
typedef struct
{

} Bank_Up_Down_Options_t;


// -----------------------------Track_Start_Stop---------------------------------
typedef struct
{

} Track_Start_Stop_Options_t;


// ----------------------------Track_Play_Rec----------------------------------
typedef struct
{

} Track_Play_Rec_Options_t;


// ---------------------------Track_Clear-----------------------------------
typedef struct
{

} Track_Clear_Options_t;


// -------------------------------Track_Undo_Redo-------------------------------
typedef struct
{

} Track_Undo_Redo_Options_t;


// ----------------------------Track_Pan----------------------------------
typedef struct
{

} Track_Pan_Options_t;


// ----------------------------All_Clear----------------------------------
typedef struct
{

} All_Clear_Options_t;


// ----------------------------Rhythm_Level----------------------------------
typedef struct
{

} Rhythm_Level_Options_t;


// ----------------------------Rhythm_Pattern----------------------------------
typedef struct
{

} Rhythm_Pattern_Options_t;


// -----------------------------Memory_Level---------------------------------
typedef struct
{

} Memory_Level_Options_t;


// -----------------------------Master_Comp---------------------------------
typedef struct
{

} Master_Comp_Options_t;


// ----------------------------Master_Reverb----------------------------------
typedef struct
{

} Master_Reverb_Options_t;


// ------------------------------Overdub_Mode--------------------------------
typedef struct
{

} Overdub_Mode_Options_t;


// ----------------------------Input_FX_On_Off----------------------------------
typedef struct
{

} Input_FX_On_Off_Options_t;


// ------------------------------Input_FX_Inc_Dec--------------------------------
typedef struct
{

} Input_FX_Inc_Dec_Options_t;


// -----------------------------Track_FX_On_Off---------------------------------
typedef struct
{

} Track_FX_On_Off_Options_t;


// ------------------------------Track_FX_Inc_Dec--------------------------------
typedef struct
{

} Track_FX_Inc_Dec_Options_t;


// ------------------------------Target_Track_Inc_Dec--------------------------------
typedef struct
{

} Target_Track_Inc_Dec_Options_t;

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


typedef union // all the possible Function Types get united
{
    Target_Track_Start_Stop_Options_t Target_Track_Start_Stop;
    Target_Track_Stop_Options_t Target_Track_Stop;
    Target_Track_Clear_Options_t Target_Track_Clear;
    Target_Track_Undo_redo_Options_t Target_Track_Undo_redo;
    Target_Track_Play_Level_Options_t Target_Track_Play_Level;
    All_Start_Stop_Options_t All_Start_Stop;
    Last_Undo_Redo_Options_t Last_Undo_Redo;
    Tap_Tempo_Options_t Tap_Tempo;
    Bank_Up_Down_Options_t Bank_Up_Down;


    Track_Start_Stop_Options_t Track_Start_Stop;
    Track_Play_Rec_Options_t Track_Play_Rec;
    Track_Clear_Options_t Track_Clear;
    Track_Undo_Redo_Options_t Track_Undo_Redo;
    Track_Pan_Options_t Track_Pan;
    All_Clear_Options_t All_Clear;
    Rhythm_Level_Options_t Rhythm_Level;
    Rhythm_Pattern_Options_t Rhythm_Pattern;
    Memory_Level_Options_t Memory_Level;
    Master_Comp_Options_t Master_Comp;
    Master_Reverb_Options_t Master_Reverb;
    Overdub_Mode_Options_t Overdub_Mode;
    Input_FX_On_Off_Options_t Input_FX_On_Off; // more options form RC-505 V1 avaiable
    Input_FX_Inc_Dec_Options_t Input_FX_Inc_Dec;
    Track_FX_On_Off_Options_t Track_FX_On_Off;
    Track_FX_Inc_Dec_Options_t Track_FX_Inc_Dec;
    Target_Track_Inc_Dec_Options_t Target_Track_Inc_Dec;

} Controll_Function_t ;

typedef struct // every Button is Configured with a Midi CC and addiditional Settings for each function
{
    uint8_t midi_CC;
    Controll_Function_t assignment;

} buttonFunction_t;


typedef struct
{
    RGB_Colors_t track_One_color;
    RGB_Colors_t track_Two_color;
    RGB_Colors_t track_Three_color;
    RGB_Colors_t track_Four_color;
    RGB_Colors_t track_Five_color;

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

bool readSettings(void);

bool writeSettings(void);

#endif // !CONFIG_H