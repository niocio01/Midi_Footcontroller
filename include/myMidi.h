#ifndef MYMIDI_H
#define MYMIDI_H

    void midiSetup(void);

    void midiInputTest (void);

    void midiOutputTest(void);

    void sendMidiCC(uint8_t cc, uint8_t val);

#endif //  MYMIDI_H