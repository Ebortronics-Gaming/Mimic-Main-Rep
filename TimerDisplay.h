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
