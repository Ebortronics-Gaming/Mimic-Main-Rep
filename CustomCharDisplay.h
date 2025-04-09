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
};

#endif
