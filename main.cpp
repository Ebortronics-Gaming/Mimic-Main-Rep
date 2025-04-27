#include "mbed.h"
#include "TextLCD_CC.h"
#include "CustomCharDisplay.h"
#include "TimerDisplay.h"
#include "PatternGenerator.h"

// single‐file class implementations
#include "joystick.cpp"
#include "buttons.cpp"
#include "player.cpp"
#include "player.cpp"   // for showWinScreen (if defined there)

#define BUTTON1_PIN USER_BUTTON1
#define BUTTON2_PIN USER_BUTTON2
#define BUTTON3_PIN USER_BUTTON3

// LCD wiring
TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);
displayClass display(lcd);
TimerDisplay  timer(lcd);
PatternGenerator generator(display);

// Inputs
joystick stick(A1, A0);
Button    btn1(BUTTON1_PIN, []{});
Button    btn2(BUTTON2_PIN, []{});
Button    btn3(BUTTON3_PIN, []{});

int main() {
    // — Initialization —
    display.begin();
    stick.begin();
    Player::reset();
    timer.updateDisplay(10); // 10-minute countdown

    while (true) {
        // — MENU & NAVIGATION —
        display.displayMenuScreen();
        if (display.currentSelection == "High Score") {
            display.displayHighScore(Player::score);
            continue;
        }
        if (display.currentSelection == "How To Play") {
            display.displayInstructions();
            continue;
        }
        if (display.currentSelection == "Game Story") {
            display.displayStory();
            continue;
        }
        if (display.currentSelection == "Settings") {
            display.displaySettings();
            continue;
        }

        // User chose Play then pick difficulty
        display.displayDifficultyPage();
        Player::setLevel(display.level);
        display.defaultDisplay();

        // — PATTERN GENERATION —
        generator.pattern(Player::arrowNum);
        int* pattern = generator.getSequence();

        // — GAME LOOP —
        while (!timer.isFinished() && !Player::isGameOver()) {
            stick.clearMoves();
            uint8_t userMoves[20];
            uint8_t moveCount = 0;

            // gather exactly arrowNum moves
            while (moveCount < Player::arrowNum) {
                stick.update();
                thread_sleep_for(100);
                stick.getMoves(userMoves, moveCount);
            }

            // compare
            bool correct = true;
            for (int i = 0; i < Player::arrowNum; ++i) {
                if (userMoves[i] != pattern[i]) {
                    correct = false;
                    break;
                }
            }

            if (correct) {
                Player::addScore();
                display.scoreUpdate();
            } else {
                Player::addMonster();
                display.updateMonsters();
            }
            thread_sleep_for(200);
        }

        // — END OF GAME —
        lcd.cls();
        if (Player::isGameOver()) {
            lcd.locate(0,0);
            lcd.printf("  GAME OVER   ");
            lcd.locate(0,1);
            lcd.printf("Score: %d", Player::score);
        } else {
            showWinScreen(lcd, Player::score);
        }
        thread_sleep_for(2000);

        // Reset for replay
        Player::reset();
        timer.updateDisplay(10);
    }
}
