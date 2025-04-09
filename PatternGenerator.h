#ifndef PATTERN_GENERATOR_H
#define PATTERN_GENERATOR_H

#include "mbed.h"
#include "TextLCD_CC.h"
#include "CustomCharDisplay.h"

class PatternGenerator {
private:
    CustomCharDisplay &display;
    int sequence[10];    
    int sequenceSize;

public:
    PatternGenerator(CustomCharDisplay &displayRef);
    void pattern(int y);         
    int* getSequence();             
    int getSequenceSize();           
};

#endif
