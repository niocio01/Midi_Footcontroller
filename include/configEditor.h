#ifndef CONFIG_EDITOR_H
#define CONFIG_EDITOR_H 

#include "config.h"


uint8_t getBank (void);

uint8_t getMidiChannel (void);

void changeBank(uint8_t newBank);

uint8_t getButtonMidiCC(uint8_t button);
Function_Type_t getButtonFunction(uint8_t button);

uint8_t getTargetTrackCC(TargetTrackCC_Type_t type);

uint8_t getButtonAddPar1(uint8_t button);
uint8_t getButtonAddPar2(uint8_t button);

#endif // !CONFIG_EDITOR_H