#ifndef CUSTOMCHARDISPLAY_H
#define CUSTOMCHARDISPLAY_H

#include "TextLCD_CC.h"
#include "player.h"
#include <cstdarg>

class CustomCharDisplay {
public:
    CustomCharDisplay(TextLCD &lcdRef);
    void welcome();
    void defaultDisplay();
    void scoreUpdate();
    void updateMonsters();
    void displayChar(int id, int col, int row);
    void cls();
    void locate(int col, int row);
    void putc(char c);
    void printf(const char* fmt, ...);
protected:
    TextLCD &lcd;
};

#endif // CUSTOMCHARDISPLAY_H
