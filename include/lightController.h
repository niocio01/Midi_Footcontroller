/*
lightController.h:
Controll the light effects of the Led's
provide functions to set the state of the buttons, that correstond to the different lighting scenarios.
 */

#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "led.h"



namespace ButtonLights
{


typedef enum buttons
{
    TRACK1_PLAY,
    TRACK1_OVD,
    TRACK2_PLAY,
    TRACK2_OVD,
    TRACK3_PLAY,
    TRACK3_OVD,
    TRACK4_PLAY,
    TRACK4_OVD,
    TRACK5_PLAY,
    TRACK5_OVD,

    CSTM_SW1,
    CSTM_SW2,
    CSTM_SW3,
    CSTM_SW4,
    CSTM_SW5

} buttons_t;

typedef enum trackState
{
    INIT,
    EMPTY,
    PAUSED,
    PLAYING,
    RECORDING,
    WAITING_FOR_PLAYING,
    WAITING_FOR_RECORDING,
    WAITING_FOR_PAUSING,

} trackState_t;

void init(void);

void setTrackState(uint8_t track, trackState_t state);

void update(void);

}; // END NAMESPACE

#endif // LIGHT_CONTROLLER_H
