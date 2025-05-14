#include "TimerDisplay.h"

TimerDisplay::TimerDisplay(TextLCD &lcdRef)
    : lcd(lcdRef), minutes(0), seconds(0), timerRunning(false), finishedFlag(0) {}

void TimerDisplay::updateDisplay(int startMinutes) {
    minutes = startMinutes - 1;
    seconds = 59;
    finishedFlag = 0;
    timerRunning = true;

    timerThread.start(callback(this, &TimerDisplay::countdownLoop));
}

void TimerDisplay::countdownLoop() {
    while (timerRunning) {
        lcd.locate(7, 0);
        lcd.printf("%01d:%02d", minutes, seconds);

        if (minutes == 0 && seconds == 0) 
        {
            timerRunning = false;
            finishedFlag = 1;
            lcd.cls();
            return;
        }

        if (seconds == 0) 
        {
            minutes--;
            seconds = 59;
        } 
        else 
        {
            seconds--;
        }

        ThisThread::sleep_for(1000ms);
    }
}

int TimerDisplay::isFinished() {
    return finishedFlag;
}
