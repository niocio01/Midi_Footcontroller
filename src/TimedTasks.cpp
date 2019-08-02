#include <Arduino.h>
#include "inputs.h"
#include "lightController.h"

namespace TimedTasks
{

#define uS_TO_TIMER_COMPARE(uS) ((uS * 15) >> 5) //Fixed point equivalent of uS / 2.13333.

#define UPDATE_INTERVALL 10000
#define UPDATE_INTERVALL_LEDS 50000
#define NO_OF_INTERUPTS_LEDS 3

uint8_t NoOfInterrupt_Led = 0;

void timerInit(void)
{
    //SIM_SCGC3 |= SIM_SCGC3_FTM3; // enable CLK

    FTM3_MODE |= FTM_MODE_WPDIS; // Write Protection Disable
    FTM3_MODE |= FTM_MODE_FTMEN; // Flex Timer module enable
    FTM3_MODE |= FTM_MODE_INIT;  // Perform init functions

    FTM3_SC = 0x00;      // Set this to zero before changing the modulus
    FTM3_CNTIN = 0x0000; //Shouldn't be needed, but just in case
    FTM3_CNT = 0x0000;   // Reset the count to zero
    FTM3_MOD = 0xFFFF;   // max modulus = 65535

    ////////////////////// Timer setup /////////////////////////
    //  Base Clock = Bus Clock = 60 MHz                       //
    //  Prescaler = 7 -> 60 MHz / 128 = 468.75kHz = 2.133uS   //
    ////////////////////////////////////////////////////////////

    FTM3_SC = FTM_SC_CLKS(1) | FTM_SC_PS(7); // select Clock, set Prescaler

    //Setup the channels (See Pg 1014 of K64 DS).
    FTM3_C0SC &= ~FTM_CSC_MSB; //According to Pg 965 of the datasheet, this should not be needed as MSB is reset to 0 upon reset, but the channel interrupt fails to fire without it
    FTM3_C0SC |= FTM_CSC_MSA;  //Enable Compare mode
    FTM3_C0SC |= FTM_CSC_CHIE; //Enable channel compare interrupt
    //Duplicate the above 3 lines for each compare channel you want active

    FTM3_C1SC &= ~FTM_CSC_MSB; //According to Pg 965 of the datasheet, this should not be needed as MSB is reset to 0 upon reset, but the channel interrupt fails to fire without it
    FTM3_C1SC |= FTM_CSC_MSA;  //Enable Compare mode
    FTM3_C1SC |= FTM_CSC_CHIE; //Enable channel compare interrupt

    NVIC_SET_PRIORITY(IRQ_FTM3, 8); // set interrupt priority
    NVIC_ENABLE_IRQ(IRQ_FTM3);      // enable interrupt

    FTM3_C0V = uS_TO_TIMER_COMPARE(UPDATE_INTERVALL);
    FTM3_C1V = uS_TO_TIMER_COMPARE(UPDATE_INTERVALL_LEDS);

    Serial.println("Timer1 Setup done");
}

volatile bool alternate = 0;

void task0(void)
{
    FTM3_C0V += uS_TO_TIMER_COMPARE(UPDATE_INTERVALL);
    inputs::InputsISR();
}

void task1(void)
{

    FTM3_C1V += uS_TO_TIMER_COMPARE(UPDATE_INTERVALL_LEDS);
    if (NoOfInterrupt_Led == NO_OF_INTERUPTS_LEDS)
    {
        NoOfInterrupt_Led = 0;
        ButtonLights::update();
    }
    else
    {
        NoOfInterrupt_Led++;
    }
}

void resetTask1(void)
{
    NoOfInterrupt_Led = 0;
}

} // namespace TimedTasks

void ftm3_isr(void)
{
    if (FTM3_C0SC & FTM_CSC_CHF)
    {
        FTM3_C0SC &= ~FTM_CSC_CHF;
        TimedTasks::task0();
    }
    if (FTM3_C1SC & FTM_CSC_CHF)
    {
        FTM3_C1SC &= ~FTM_CSC_CHF;
        TimedTasks::task1();
    }
    // if (FTM3_C2SC & FTM_CSC_CHF) { FTM3_C2SC &= ~FTM_CSC_CHF; task2(); }
    // if (FTM3_C3SC & FTM_CSC_CHF) { FTM3_C3SC &= ~FTM_CSC_CHF; task3(); }
    // if (FTM3_C4SC & FTM_CSC_CHF) { FTM3_C4SC &= ~FTM_CSC_CHF; task4(); }
    // if (FTM3_C5SC & FTM_CSC_CHF) { FTM3_C5SC &= ~FTM_CSC_CHF; task5(); }
    // if (FTM3_C6SC & FTM_CSC_CHF) { FTM3_C6SC &= ~FTM_CSC_CHF; task6(); }
    // if (FTM3_C7SC & FTM_CSC_CHF) { FTM3_C7SC &= ~FTM_CSC_CHF; task7(); }
}
