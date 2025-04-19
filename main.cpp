// main.cpp

#include "mbed.h"
#include "TextLCD_CC.h"
#include "CustomCharDisplay.h"
#include "TimerDisplay.h"
#include "PatternGenerator.h"
#include "joystick.cpp"
#include "buttons.cpp"
#include "player.cpp"

// LCD & display objects
TextLCD lcd(D0, D1, D2, D3, D4, D5, TextLCD::LCD16x2);
CustomCharDisplay display(lcd);
TimerDisplay      timer(lcd);
PatternGenerator  generator(display);

// Button callbacks
void btn1Action() { 
    printf("Button 1 pressed\n"); 
    Player::nextLevel(); 
}
void btn2Action() { 
    printf("Button 2 pressed\n"); 
    // TODO: implement BACK action 
}
void btn3Action() { 
    printf("Button 3 pressed\n"); 
    // TODO: implement ENTER/PLAY action 
}

// Hook up physical buttons (pins D12, D11, D10)
Button btn1(D12, btn1Action);
Button btn2(D11, btn2Action);
Button btn3(D10, btn3Action);

// Utility: compare two int arrays
static bool arraysAreEqual(const int* a, const int* b, int size) {
    for (int i = 0; i < size; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// End‑of‑game screens (unchanged)
static void showLoseScreen(TextLCD &lcd, int score) {
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

static void showWinScreen(TextLCD &lcd, int score) {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("    YOU WON!   ");
    lcd.locate(0, 1);
    lcd.printf("Your Score : %d", score);
    thread_sleep_for(2000);

    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("   Well Done!   ");
    lcd.locate(0, 1);
    lcd.printf(" Rest Your Eyes ");
    thread_sleep_for(2000);
}

// Core level loop
static void playLevel(int durationMinutes) {
    // show loading + “Level X” + “Go”
    display.welcome();

    // initial HUD: arrows, timer icon, hearts, monsters, player
    display.defaultDisplay();

    // start countdown timer (minutes)
    timer.updateDisplay(durationMinutes);

    // play until time runs out or lives/monsters exhausted
    while (!timer.isFinished()
           && Player::hearts   > 0
           && Player::monsterNum > 0) 
    {
        // flash a pattern of length arrowNum
        int len = Player::arrowNum;
        generator.pattern(len);

        // get generated and user sequences
        int* seq  = generator.getSequence();
        int* user = joystick.pattern(len);

        if (arraysAreEqual(seq, user, len)) {
            // correct: +1 score, update display, decrement monster count
            Player::addScore(1);
            display.scoreUpdate();
            Player::minusMonster();
            display.updateMonsters();
        } else {
            // wrong: lose a heart, update display
            Player::minusHearts();
            display.updateLives();
        }

        // brief pause before next round
        thread_sleep_for(200);
    }

    // show appropriate end‐of‐level screen
    if (Player::monsterNum == 0) {
        showWinScreen(lcd, Player::score);
    } else {
        showLoseScreen(lcd, Player::score);
    }
}

int main() {
    // reset everything to level 1
    Player::ResetLevel();

    // durations per level in minutes (adjust as preferred)
    const int levelDurations[4] = { 8, 6, 8, 6 };

    // run through all 4 levels
    for (int lvl = 1; lvl <= 4; ++lvl) {
        Player::setLevel(lvl);
        playLevel(levelDurations[lvl - 1]);

        // if player lost (hearts == 0), stop advancing
        if (Player::hearts == 0) {
            break;
        }
    }

    // keep program alive
    while (true) {
        thread_sleep_for(1000);
    }
}
