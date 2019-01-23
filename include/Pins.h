#include <core_pins.h>

#ifndef PINS_H
#define PINS_H

///////////////////// MENU BUTTONS /////////////////////

#define BTN_BK_UP_PIN       5
#define BTN_BK_DWN_PIN      6
#define BTN_MODE_PIN        4
#define BTN_BACK_PIN        3
#define BTN_SAVE_PIN        2
#define BTN_SELECT_PIN      7

#define BTN_BK_UP_CONFIG    CORE_PIN5_CONFIG
#define BTN_BK_DWN_CONFIG   CORE_PIN6_CONFIG
#define BTN_MODE_CONFIG     CORE_PIN4_CONFIG
#define BTN_BACK_CONFIG     CORE_PIN3_CONFIG
#define BTN_SAVE_CONFIG     CORE_PIN2_CONFIG
#define BTN_SELECT_CONFIG   CORE_PIN7_CONFIG

#define BTN_BK_UP_PINMASK   CORE_PIN5_PINREG & CORE_PIN5_BITMASK 
#define BTN_BK_DWN_PINMASK  CORE_PIN6_PINREG & CORE_PIN6_BITMASK
#define BTN_MODE_PINMASK    CORE_PIN4_PINREG & CORE_PIN4_BITMASK
#define BTN_BACK_PINMASK    CORE_PIN3_PINREG & CORE_PIN3_BITMASK
#define BTN_SAVE_PINMASK    CORE_PIN2_PINREG & CORE_PIN2_BITMASK
#define BTN_SELECT_PINMASK  CORE_PIN7_PINREG & CORE_PIN7_BITMASK


///////////////////// ENCODER /////////////////////

#define ENCODER_CLK_PIN     9
#define ENCODER_DT_PIN      8

#define ENCODER_CLK_CONFIG  CORE_PIN9_CONFIG
#define ENCODER_DT_CONFIG   CORE_PIN8_CONFIG

#define ENCODER_CLK_PINMASK CORE_PIN9_PINREG & CORE_PIN9_BITMASK
#define ENCODER_DT_PINMASK  CORE_PIN8_PINREG & CORE_PIN8_BITMASK


///////////////////// PEDAL /////////////////////

#define PEDAL_PIN           17

#define PEDAL_CONFIG        CORE_PIN17_CONFIG

#define PEDAL_PINMASK        CORE_PIN17_CONFIG | PORT_PCR_ISF


///////////////////// RX, TX FOR MIDI /////////////////////

#define MIDI_IN_PIN         0
#define MIDI_OUT_PIN        1


///////////////////// SWITCHES /////////////////////

// TRACK PLAY, OVERDUB
#define TRACK1_PLAY_PIN     37
#define TRACK1_OVD_PIN      29
#define TRACK2_PLAY_PIN     38
#define TRACK2_OVD_PIN      28
#define TRACK3_PLAY_PIN     39
#define TRACK3_OVD_PIN      27
#define TRACK4_PLAY_PIN     25
#define TRACK4_OVD_PIN      26
#define TRACK5_PLAY_PIN     13
#define TRACK5_OVD_PIN      24

#define TRACK1_PLAY_CONFIG   CORE_PIN37_CONFIG
#define TRACK1_OVD_CONFIG    CORE_PIN29_CONFIG
#define TRACK2_PLAY_CONFIG   CORE_PIN38_CONFIG
#define TRACK2_OVD_CONFIG    CORE_PIN28_CONFIG
#define TRACK3_PLAY_CONFIG   CORE_PIN39_CONFIG
#define TRACK3_OVD_CONFIG    CORE_PIN27_CONFIG
#define TRACK4_PLAY_CONFIG   CORE_PIN25_CONFIG
#define TRACK4_OVD_CONFIG    CORE_PIN26_CONFIG
#define TRACK5_PLAY_CONFIG   CORE_PIN13_CONFIG
#define TRACK5_OVD_CONFIG    CORE_PIN24_CONFIG

#define TRACK1_PLAY_PINMASK  CORE_PIN37_PINREG & CORE_PIN37_BITMASK
#define TRACK1_OVD_PINMASK   CORE_PIN29_PINREG & CORE_PIN29_BITMASK
#define TRACK2_PLAY_PINMASK  CORE_PIN38_PINREG & CORE_PIN38_BITMASK
#define TRACK2_OVD_PINMASK   CORE_PIN28_PINREG & CORE_PIN28_BITMASK
#define TRACK3_PLAY_PINMASK  CORE_PIN39_PINREG & CORE_PIN39_BITMASK
#define TRACK3_OVD_PINMASK   CORE_PIN27_PINREG & CORE_PIN27_BITMASK
#define TRACK4_PLAY_PINMASK  CORE_PIN25_PINREG & CORE_PIN25_BITMASK
#define TRACK4_OVD_PINMASK   CORE_PIN26_PINREG & CORE_PIN26_BITMASK
#define TRACK5_PLAY_PINMASK  CORE_PIN13_PINREG & CORE_PIN13_BITMASK
#define TRACK5_OVD_PINMASK   CORE_PIN24_PINREG & CORE_PIN24_BITMASK


// CUSTOM SWITCHES
#define CSTM_SW1_PIN         30
#define CSTM_SW2_PIN         31
#define CSTM_SW3_PIN         32
#define CSTM_SW4_PIN         35
#define CSTM_SW5_PIN         34

#define CSTM_SW1_CONFIG      CORE_PIN30_CONFIG
#define CSTM_SW2_CONFIG      CORE_PIN31_CONFIG
#define CSTM_SW3_CONFIG      CORE_PIN32_CONFIG
#define CSTM_SW4_CONFIG      CORE_PIN35_CONFIG
#define CSTM_SW5_CONFIG      CORE_PIN34_CONFIG

#define CSTM_SW1_PINMASK     CORE_PIN30_PINREG & CORE_PIN30_BITMASK
#define CSTM_SW2_PINMASK     CORE_PIN31_PINREG & CORE_PIN31_BITMASK
#define CSTM_SW3_PINMASK     CORE_PIN32_PINREG & CORE_PIN32_BITMASK
#define CSTM_SW4_PINMASK     CORE_PIN35_PINREG & CORE_PIN35_BITMASK
#define CSTM_SW5_PINMASK     CORE_PIN34_PINREG & CORE_PIN34_BITMASK


///////////////////// OTHER PINS /////////////////////

// I2C MULTIPLEXER RESET
#define I2C_MUX_RESET_PIN   10

// LED DRIVER RESET
#define LED_DRVR1_RESET_PIN 16
#define LED_DRVR2_RESET_PIN 17

// BUILT IN LED
#define TEENSY_LED_PIN 13

#endif