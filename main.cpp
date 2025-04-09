#include "mbed.h"
#include "joystick.cpp"
#include "buttons.cpp"
#include "display.cpp"
#include "player.cpp"
#include "patterns.cpp"
#include <cstdio>
#include <limits>
#include <stdio.h>
#include <array>

Player player;

void btn1Action();
void btn2Action();
void btn3Action();

// Button objects with different pins & callbacks
Button btn1(D12, btn1Action);    // level changing button
Button btn2(D11, btn2Action);
Button btn3(D10, btn3Action);

#include "mbed.h"
#include "TextLCD_CC.h"
#include "TimerDisplay.h"
#include "CustomCharDisplay.h"
#include "PatternGenerator.h"

TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);
CustomCharDisplay display(lcd);
TimerDisplay timer(lcd);
PatternGenerator generator(display);


int main() {
    /*==============================Level 1==============================*/

    if(level == 1)
    {
        display.welcome(); 
        thread_sleep_for(2000);
        lcd.cls();
        display.defaultDisplay();
        timer.updateDisplay(8);

        int i = 0;
        int score = 0;

        while(exit != 1 && 15-(i+1) != 1 && timer.isFinished() != 1)
        {
            generator.pattern(4); 
            int* seq = generator.getSequence();
            int* user = joystick.pattern(4);

            bool arraysAreEqual(int a[], int b[]) 
            {
                for (int j = 0; j < 4; j++) 
                {
                    if (a[j] != b[j]) 
                    {
                        return false; 
                    }
                }
                return true;
            }

            if (arraysAreEqual(seq, user)) 
            {
                check = 2;
                score += 1;
                display.scoreUpdate();
                lcd.locate(13,0);
                lcd.printf("%d", score);

            } 
            else 
            {
                check = 1;
            }

            if(check == 1)
            {
                display.displayChar(3, 15-(i+1), 1);
                thread_sleep_for(500);
                ++i;
                check = 0;
            }
            else if(check == 2)
            {
                display.displayChar(3, 15-(i+1), 1);
                thread_sleep_for(500);
                display.displayChar(10, 15-(i+1), 1);
                check = 0;
            }
        }

        if(timer.isFinished() == 1)
        {
            showWinScreen(lcd, score);
        }
        if(15-(i+1) == 1)
        {
            showLoseScreen(lcd, score);
        }
    }

    /*==============================Level 2==============================*/ 

    if(level == 2)
    {
        display.welcome();
        thread_sleep_for(2000);
        lcd.cls();
        display.defaultDisplay();
        timer.updateDisplay(6);

        int i = 0;
        int score = 0;

        while(exit != 1 && 15-(i+1) != 1 && timer.isFinished() != 1)
        {
            generator.pattern(6); 
            int* seq = generator.getSequence();
            int* user = joystick.pattern(6);

            bool arraysAreEqual(int a[], int b[]) 
            {
                for (int j = 0; j < 6; j++) 
                {
                    if (a[j] != b[j]) 
                    {
                        return false; 
                    }
                }
                return true;
            }

            if (arraysAreEqual(seq, user)) 
            {
                check = 2;
                score += 1;
                display.scoreUpdate();
                lcd.locate(13,0);
                lcd.printf("%d", score);
            } 
            else 
            {
                check = 1;
            }

            if(check == 1)
            {
                display.displayChar(3, 15-(i+1), 1);
                thread_sleep_for(500);
                ++i;
                check = 0;
            }
            else if(check == 2)
            {
                display.displayChar(3, 15-(i+1), 1);
                thread_sleep_for(500);
                display.displayChar(10, 15-(i+1), 1);
                check = 0;
            }
        }
        
        if(timer.isFinished() == 1)
        {
            showWinScreen(lcd, score);
        }
        if(15-(i+1) == 1)
        {
            showLoseScreen(lcd, score);
        }
    }

    /*==============================Level 3==============================*/

    if(level == 3)
    {
        display.welcome();
        thread_sleep_for(2000);
        lcd.cls();
        display.defaultDisplay();
        timer.updateDisplay(8);

        int i = 0;
        int score = 0;

        while(exit != 1 && 15-(i+1) != 1 && timer.isFinished() != 1)
        {
            generator.pattern(8); 
            int* seq = generator.getSequence();
            int* user = joystick.pattern(8);

            bool arraysAreEqual(int a[], int b[]) 
            {
                for (int j = 0; j < 8; j++) 
                {
                    if (a[j] != b[j]) 
                    {
                        return false; 
                    }
                }
                return true;
            }

            if (arraysAreEqual(seq, user)) 
            {
                check = 2;
                score += 1;
                display.scoreUpdate();
                lcd.locate(13,0);
                lcd.printf("%d", score);
            } 
            else 
            {
                check = 1;
            }

            if(check == 1)
            {
                display.displayChar(3, 15-(i+1), 1);
                thread_sleep_for(500);
                ++i;
                check = 0;
            }
            else if(check == 2)
            {
                display.displayChar(3, 15-(i+1), 1);
                thread_sleep_for(500);
                display.displayChar(10, 15-(i+1), 1);
                check = 0;
            }
        }

        if(timer.isFinished() == 1)
        {
            showWinScreen(lcd, score);
        }
        if(15-(i+1) == 1)
        {
            showLoseScreen(lcd, score);
        }
    }

    while (true) { }
    
}

void showLoseScreen(TextLCD &lcd, int score) {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("   YOU LOOSED!   ");
    lcd.locate(0, 1);
    lcd.printf("Your Score : %d", score);
    thread_sleep_for(2000);

    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("  Take a Break  ");
    lcd.locate(0, 1);
    lcd.printf("Try Again Later!");
    thread_sleep_for(2000);
}

void showWinScreen(TextLCD &lcd, int score) {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("    YOU WON!   ");
    lcd.locate(0,1);
    lcd.printf("Your Score : %d", score);
    thread_sleep_for(2000);
    
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("   Well Done!   ");
    lcd.locate(0,1);
    lcd.printf(" Rest Your Eyes ");
    thread_sleep_for(2000);
}


// Button Action Functions:
void btn1Action() {     // increases level
    printf("Button 1 is pressed\n");
    player.NextLevel();
}

void btn2Action() {
    printf("Button 2 is pressed\n");
    // to be continued...
}

void btn3Action() {
    printf("Button 3 is pressed\n");
    // to be continued...
}
