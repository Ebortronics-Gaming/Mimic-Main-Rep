#ifndef PATTERN_GENERATOR_H
#define PATTERN_GENERATOR_H

#include "mbed.h"
#include "TextLCD_CC.h"

class display; // Forward declaration

class PatternGenerator {
private:
    display &disp;
    int sequence[10];    
    int sequenceSize;

public:
    PatternGenerator(display &dispRef);
    void pattern(int y);         
    int* getSequence();             
    int getSequenceSize();           
};

#endif
