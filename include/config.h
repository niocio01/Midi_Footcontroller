#ifndef CONFIG_H
#define CONFIG_H 

#include <Arduino.h>

typedef struct config // master Struct Of current Config
{
    int currentBank;
    buttonFunction_t function [16];

} config_t;

typedef struct buttonFunction // every Button is Configured with a Midi CC and addiditional Settings for each function
{
    uint8_t midi_CC;
    Controll_Function_t assignment;

} buttonFunction_t;

typedef union Controll_Function // all the possible Function Types get united
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
    Target_Track_Inc_Dec

} Controll_Function_t ;




// Individual Functions Structs with corresponding options

// -----------------------Target_Track_Start_Stop--------------------------------
typedef struct
{
    Target_Track_Start_Stop_Modes_t mode;
    
} Target_Track_Start_Stop_Options_t ;

typedef enum {
    SINGLE,
    MULTI,    
} Target_Track_Start_Stop_Modes_t;


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


// --------------------------------------------------------------
typedef struct
{

} _Options_t;


// --------------------------------------------------------------
typedef struct
{

} _Options_t;


// --------------------------------------------------------------
typedef struct
{

} _Options_t;





#endif // !CONFIG_H