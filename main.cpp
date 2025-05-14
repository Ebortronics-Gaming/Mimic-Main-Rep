#include "mbed.h"
#include "TextLCD_CC.h"
#include "joystick.h"
#include "buttons.h"
#include "player.h"
#include "display.h"
#include "PatternGenerator.h"
#include "TimerDisplay.h"
#include <cstdlib>
#include <ctime>

#define PIN_BUTTON_HOME   D6
#define PIN_BUTTON_BACK   D7
#define PIN_BUTTON_ENTER  D8
#define PIN_JOY_X         A0
#define PIN_JOY_Y         A1
#define GAME_DURATION_MIN 10

// Global flags set by ISRs
volatile bool homePressed  = false;
volatile bool enterPressed = false;
volatile bool backPressed  = false;

// ISR callbacks
void onHome()  { homePressed  = true; }
void onEnter() { enterPressed = true; }
void onBack()  { backPressed  = true; }

int main() {
    // Seed RNG once
    srand(time(NULL));

    // 4-bit LCD wiring: RS=D0, E=D1, DB4–DB7=D2–D5
    TextLCD lcd(
        D0, D1,
        D2, D3, D4, D5,
        TextLCD::LCD16x2
    );

    // Instantiate everything
    display         disp(lcd, PIN_BUTTON_HOME, PIN_BUTTON_BACK, PIN_BUTTON_ENTER);
    Joystick        stick(PIN_JOY_X, PIN_JOY_Y);
    PatternGenerator generator(disp);
    TimerDisplay    timer(lcd);

    // Hook up button interrupts
    Button btnHome(PIN_BUTTON_HOME,  onHome);
    Button btnEnter(PIN_BUTTON_ENTER, onEnter);
    Button btnBack(PIN_BUTTON_BACK,   onBack);

    // Init
    disp.begin();
    stick.begin();
    Player::reset();

    // Show welcome animation once
    disp.displayWelcomeMessage("Loading...");

    // Our state-machine
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
            case STATE_MENU:
                disp.displayMenuScreen(stick, enterPressed, homePressed, backPressed);
                if      (disp.currentSelection == "High Score")   state = STATE_HIGHSCORE;
                else if (disp.currentSelection == "How To Play")  state = STATE_HOWTO;
                else if (disp.currentSelection == "Game Story")   state = STATE_STORY;
                else if (disp.currentSelection == "Settings")     state = STATE_SETTINGS;
                else /* "Play" */                                 state = STATE_DIFFICULTY;
                enterPressed = homePressed = backPressed = false;
                break;

            case STATE_HIGHSCORE:
                disp.displayHighScore(Player::score);
                state = STATE_MENU;
                break;

            case STATE_HOWTO:
                disp.displayInstructions(stick, enterPressed, backPressed, homePressed);
                state = STATE_MENU;
                break;

            case STATE_STORY:
                disp.displayStory(stick, enterPressed, backPressed, homePressed);
                state = STATE_MENU;
                break;

            case STATE_SETTINGS:
                disp.displaySettings(stick, enterPressed, backPressed, homePressed);
                state = STATE_MENU;
                break;

            case STATE_DIFFICULTY:
                disp.displayDifficultyPage(stick, enterPressed, backPressed, homePressed);
                if (enterPressed) {
                    Player::setLevel(disp.level);
                    timer.updateDisplay(GAME_DURATION_MIN);
                    state = STATE_PLAY;
                } else {
                    state = STATE_MENU;
                }
                enterPressed = homePressed = backPressed = false;
                break;

            case STATE_PLAY: {
                disp.defaultDisplay();
                generator.pattern(Player::arrowNum);
                int* pattern = generator.getSequence();
                uint8_t moveCount = 0, userMoves[20];
                Timer inputTimer; 
                inputTimer.start();
                homePressed = false;

                while (moveCount < Player::arrowNum
                       && inputTimer.read_ms() < 1000
                       && !homePressed) {
                    stick.update();
                    stick.getMoves(userMoves, moveCount);
                    ThisThread::sleep_for(50);
                }
                inputTimer.stop();

                bool correct = true;
                for (int i = 0; i < Player::arrowNum; ++i) {
                    if (userMoves[i] != pattern[i]) {
                        correct = false;
                        break;
                    }
                }

                if (correct) {
                    Player::addScore();
                    disp.scoreUpdate();
                } else {
                    Player::addMonster();
                    disp.updateMonsters();
                }

                if      (homePressed)           state = STATE_MENU;
                else if (Player::isGameOver())  state = STATE_GAMEOVER;
                else if (timer.isFinished())    state = STATE_WIN;
            }   break;

            case STATE_GAMEOVER:
                disp.displayGameOverScreen(Player::monsterNum);
                state = STATE_MENU;
                break;

            case STATE_WIN:
                disp.displayWinScreen(Player::score);
                state = STATE_MENU;
                break;
        }

        ThisThread::sleep_for(50);
    }
}
