// -----------------------------------------------------------------------------------
// Developed by Vishwa (Do not modify without prior discussion)
// Last Modified : 09 April 2025 by author 
// Please consult the original author before making any changes to ensure consistency
// -----------------------------------------------------------------------------------

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
