// File: main.cpp

#include "mbed.h"
#include "TextLCD_CC.h"

#include "joystick.h"           // joystick.begin(), update(), clearMoves(), getMoves()
#include "buttons.h"            // Button interrupt abstraction (if you need it)
#include "player.h"             // static Player::reset(), setLevel(), addScore(), addMonster(), isGameOver()
#include "displayClass.h"       // displayClass.begin(), displayMenuScreen(), displayXXX()...
#include "PatternGenerator.h"   // PatternGenerator::pattern(), getSequence(), getSequenceSize()
#include "TimerDisplay.h"       // timer.updateDisplay(), timer.isFinished()

// —————————————— YOUR HARDWARE PINOUT ——————————————
// Buttons on D6, D7, D8 (Home, Back, Enter)
#define PIN_BUTTON_HOME   D6
#define PIN_BUTTON_BACK   D7
#define PIN_BUTTON_ENTER  D8

// Joystick axes on A0 (X), A1 (Y)
#define PIN_JOY_X         A0
#define PIN_JOY_Y         A1

// Game runs for 10 minutes
#define GAME_DURATION_MIN 10

// ————————————————————————————————————————————————————————

int main() {
    // 1) Construct & wire up all your peripherals
    TextLCD_CC     lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);
    displayClass   display(lcd, PIN_BUTTON_HOME, PIN_BUTTON_BACK, PIN_BUTTON_ENTER);
    joystick       stick(PIN_JOY_X, PIN_JOY_Y);
    PatternGenerator generator(display);
    TimerDisplay   timer(lcd);

    // 2) Reset everything to a known state
    display.begin();       // clear screen, load custom chars, etc.
    stick.begin();         // clear joystick buffer
    Player::reset();       // score=0, level=1, arrowNum=4, monsterNum=0

    // 3) Our state machine
    enum State {
        STATE_MENU,
        STATE_HIGHSCORE,
        STATE_HOWTO,
        STATE_STORY,
        STATE_SETTINGS,
        STATE_DIFFICULTY,
        STATE_PLAY,
        STATE_GAMEOVER,
        STATE_WIN
    };
    State state = STATE_MENU;

    while (true) {
        switch (state) {
            // ——————————————————————————————— MENU & NAVIGATION ―――――――――――
            case STATE_MENU:
                // Show your main menu (High Score, How To Play, Game Story, Settings, Play)
                display.displayMenuScreen();
                // The displayClass should set display.currentSelection to one of:
                //   "High Score", "How To Play", "Game Story", "Settings", or "Play"
                if (display.currentSelection == "High Score") {
                    state = STATE_HIGHSCORE;
                } else if (display.currentSelection == "How To Play") {
                    state = STATE_HOWTO;
                } else if (display.currentSelection == "Game Story") {
                    state = STATE_STORY;
                } else if (display.currentSelection == "Settings") {
                    state = STATE_SETTINGS;
                } else if (display.currentSelection == "Play") {
                    state = STATE_DIFFICULTY;
                }
                break;

            case STATE_HIGHSCORE:
                // Pong your stored high score
                display.displayHighScore(Player::score);
                state = STATE_MENU;
                break;

            case STATE_HOWTO:
                // Show instructions
                display.displayInstructions();
                state = STATE_MENU;
                break;

            case STATE_STORY:
                // Show game story
                display.displayStory();
                state = STATE_MENU;
                break;

            case STATE_SETTINGS:
                // Show settings screen
                display.displaySettings();
                state = STATE_MENU;
                break;

            // ——————————————————————————————— DIFFICULTY PICK ―――――――――――
            case STATE_DIFFICULTY:
                // Let user pick level 1–3 (or more)
                display.displayDifficultyPage();
                // The displayClass writes the chosen level into display.level
                Player::setLevel(display.level);
                // Start the 10-minute countdown
                timer.updateDisplay(GAME_DURATION_MIN);
                state = STATE_PLAY;
                break;

            // ——————————————————————————————— GAMEPLAY LOOP ―――――――――――
            case STATE_PLAY: {
                // Draw the HUD: arrows, timer, score, monsters, player icon
                display.defaultDisplay();

                // 1) Generate & flash new pattern of length arrowNum
                generator.pattern(Player::arrowNum);
                int* pattern = generator.getSequence();
                int  patLen  = generator.getSequenceSize();

                // 2) Record exactly arrowNum joystick moves
                stick.clearMoves();
                uint8_t userMoves[20];
                uint8_t moveCount = 0;
                while (moveCount < Player::arrowNum) {
                    stick.update();
                    ThisThread::sleep_for(100);
                    stick.getMoves(userMoves, moveCount);
                }

                // 3) Compare
                bool correct = true;
                for (int i = 0; i < Player::arrowNum; ++i) {
                    if (userMoves[i] != pattern[i]) {
                        correct = false;
                        break;
                    }
                }

                if (correct) {
                    // +1 point
                    Player::addScore();
                    display.scoreUpdate();
                } else {
                    //  +1 monster (mistake)
                    Player::addMonster();
                    display.updateMonsters();
                }

                // 4) Check for end‐of‐game
                if (Player::isGameOver()) {
                    state = STATE_GAMEOVER;
                } else if (timer.isFinished()) {
                    state = STATE_WIN;
                }
                // else stay in STATE_PLAY for next round
            }   break;

            // ——————————————————————————————— GAME OVER / WIN ―――――――――――
            case STATE_GAMEOVER:
                // Show a Game Over screen & final score
                display.displayGameOverScreen(Player::monsterNum);
                state = STATE_MENU;
                break;

            case STATE_WIN:
                // Show Win screen & final score
                display.displayWinScreen(Player::score);
                state = STATE_MENU;
                break;
        }

        // small delay to debounce / avoid busy‐spin
        ThisThread::sleep_for(50);
    }
}
