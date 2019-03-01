#ifndef MYMIDI_H
#define MYMIDI_H

#define NO_COMMAND 119

    typedef struct midiCommand
    {
        uint8_t cc;
        uint8_t val;
    }midiCommand_t ;
    

    void addMidiCommandToQueue(uint8_t cc , uint8_t val);

    void SetSendQueuedCommandsFlag (void);

    void midiSetup(void);

    void midiUpdate(void);

    void handleStart(void);
    void handleClock(void);

    void sendMidiCC(uint8_t cc, uint8_t val);

#endif //  MYMIDI_H