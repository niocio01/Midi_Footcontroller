#include "inputs.h"
#include "Pins.h"

// ENABLE INPUT-PULLDOWN
// Set Pint as GPIO
#define DIGITALINPUT PORT_PCR_PE | PORT_PCR_MUX(1)

#define ANALOGINPUT PORT_PCR_MUX(1)


void initInputs (void)
{

    BTN_BK_UP_CONFIG = DIGITALINPUT;
    BTN_BK_DWN_CONFIG = DIGITALINPUT;
    BTN_MODE_CONFIG = DIGITALINPUT;
    BTN_SAVE_CONFIG = DIGITALINPUT;
    BTN_BACK_CONFIG = DIGITALINPUT;
    BTN_SELECT_CONFIG = DIGITALINPUT;

    ENCODER_CLK_CONFIG = DIGITALINPUT;
    ENCODER_DT_CONFIG = DIGITALINPUT;

    PEDAL_CONFIG = ANALOGINPUT;

    TRACK1_PLAY_CONFIG = DIGITALINPUT;
    TRACK1_OVD_CONFIG = DIGITALINPUT;
    TRACK2_PLAY_CONFIG = DIGITALINPUT;
    TRACK2_OVD_CONFIG = DIGITALINPUT;
    TRACK3_PLAY_CONFIG = DIGITALINPUT;
    TRACK3_OVD_CONFIG = DIGITALINPUT;
    TRACK4_PLAY_CONFIG = DIGITALINPUT;
    TRACK4_OVD_CONFIG = DIGITALINPUT;
    TRACK5_PLAY_CONFIG = DIGITALINPUT;
    TRACK5_OVD_CONFIG = DIGITALINPUT;

    CSTM_SW1_CONFIG = DIGITALINPUT;
    CSTM_SW2_CONFIG = DIGITALINPUT;
    CSTM_SW3_CONFIG = DIGITALINPUT;
    CSTM_SW4_CONFIG = DIGITALINPUT;
    CSTM_SW5_CONFIG = DIGITALINPUT;




SIM_SCGC6 |= SIM_SCGC6_FTM1 ; // enable CLK

////////////////// Timer setup //////////////////////
// Base Clock = System Clock = 120 MHz            //
// Prescaler = 7 -> 120 MHz / 128 = 937.5kHz          //


FTM1_SC = FTM_SC_CLKS(7) | FTM_SC_PS(1) ; // select Clock, set Prescaler

FTM1_C0SC = FTM_CSC_CHIE; // enable Interrupt for channel 1


}

static uint32_t inputBuffer = 0;
static uint32_t lastInputBuffer = 0;

static uint32_t debouncedInputBuffer = 0;

void FTM1_IRQHandler (void)
{

    if (FTM1_C0SC & FTM_CSC_CHF)
    {
        FTM1_C0SC |= ~FTM_CSC_CHF; // reset IQR
        FTM1_C0V += 9375; // do this task every 10ms (937.5kHz * 9375 = 10ms)

        // fill the current staus into the buffer to get one combined buffer
        inputBuffer = ((BTN_BK_UP_PINMASK)? 1 : 0)
                      | (1<<((BTN_BK_DWN_PINMASK)? 1 : 0))
                      | (2<<((BTN_BK_DWN_PINMASK)? 1 : 0))
                      | (3<<((BTN_MODE_PINMASK)? 1 : 0))
                      | (4<<((BTN_SAVE_PINMASK)? 1 : 0))
                      | (5<<((BTN_BACK_PINMASK)? 1 : 0))
                      | (6<<((BTN_SELECT_PINMASK)? 1 : 0))
                      | (7<<((TRACK1_PLAY_CONFIG)? 1 : 0))
                      | (8<<((TRACK1_OVD_CONFIG)? 1 : 0))
                      | (9<<((TRACK2_PLAY_CONFIG)? 1 : 0))
                      | (10<<((TRACK2_OVD_CONFIG)? 1 : 0))
                      | (11<<((TRACK3_PLAY_CONFIG)? 1 : 0))
                      | (12<<((TRACK3_OVD_CONFIG)? 1 : 0))
                      | (13<<((TRACK4_PLAY_CONFIG)? 1 : 0))
                      | (14<<((TRACK4_OVD_CONFIG)? 1 : 0))
                      | (15<<((TRACK5_PLAY_CONFIG)? 1 : 0))
                      | (16<<((TRACK5_OVD_CONFIG)? 1 : 0))
                      | (17<<((CSTM_SW1_PINMASK)? 1 : 0))
                      | (18<<((CSTM_SW2_PINMASK)? 1 : 0))
                      | (19<<((CSTM_SW3_PINMASK)? 1 : 0))
                      | (20<<((CSTM_SW4_PINMASK)? 1 : 0))
                      | (21<<((CSTM_SW5_PINMASK)? 1 : 0));

        // if the buffer didn't change, eighter because nothing happended,
        // or because the previously pressed Button has finished bouncing 
        // write the current state to the debounced buffer
        if (inputBuffer == lastInputBuffer) 
        {
            debouncedInputBuffer = inputBuffer;
        }

    // write the current Buffer as LastBuffer for the next time
    lastInputBuffer = inputBuffer;
                      
    }
    
}