// -----------------------------------------------------------------------------------
// Developed by Vishwa (Do not modify without prior discussion)
// Last Modified : 09 April 2025 by author 
// Please consult the original author before making any changes to ensure consistency
// -----------------------------------------------------------------------------------

#ifndef TIMERDISPLAY_H
#define TIMERDISPLAY_H

#include "mbed.h"
#include "TextLCD_CC.h"

class TimerDisplay {
private:
    TextLCD &lcd;
    int minutes;
    int seconds;
    bool timerRunning;
    Thread timerThread;
    int finishedFlag;

    void countdownLoop();

public:
    TimerDisplay(TextLCD &lcdRef);
    void updateDisplay(int startMinutes); 
    int isFinished();
};

#endif
