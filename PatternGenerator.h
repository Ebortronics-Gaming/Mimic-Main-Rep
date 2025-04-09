#ifndef PATTERN_GENERATOR_H
#define PATTERN_GENERATOR_H

#include "mbed.h"
#include "TextLCD_CC.h"
#include "CustomCharDisplay.h"

class PatternGenerator {
private:
    CustomCharDisplay &display;
    int sequence[10];     // Max size support up to 10 steps
    int sequenceSize;

public:
    PatternGenerator(CustomCharDisplay &displayRef);
    void pattern(int y);             // Run pattern sequence y times
    int* getSequence();              // Return pointer to the sequence array
    int getSequenceSize();           // Return size of the sequence
};

#endif
