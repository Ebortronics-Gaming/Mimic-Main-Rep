// -----------------------------------------------------------------------------------
// Developed by Vishwa (Do not modify without prior discussion)
// Last Modified : 09 April 2025 by author 
// Please consult the original author before making any changes to ensure consistency
// -----------------------------------------------------------------------------------

#ifndef CUSTOMCHARDISPLAY_H
#define CUSTOMCHARDISPLAY_H

#include "TextLCD_CC.h"

class CustomCharDisplay {
private:
    TextLCD &lcd;

public:
    CustomCharDisplay(TextLCD &lcdRef);
    void displayChar(int input, int col, int row);
    void defaultDisplay();
    void scoreUpdate();
    void welcome();
};

#endif
