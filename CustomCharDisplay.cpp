// File: CustomCharDisplay.cpp

#include "CustomCharDisplay.h"
#include "mbed.h"
#include "player.cpp"   // static Player::score, Player::monsterNum

// Constructor: load 0–6 into CGRAM (timer, heart, arrows, player)
CustomCharDisplay::CustomCharDisplay(TextLCD &lcdRef)
    : lcd(lcdRef)
{
    static char timer_[8]    = {0b01110,0b11101,0b11011,0b11111,0b01110,0b00000,0b00000,0b00000};
    static char heart_[8]    = {0b01010,0b11111,0b11111,0b01110,0b00100,0b00000,0b00000,0b00000};
    static char up_[8]       = {0b00000,0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00000};
    static char down_[8]     = {0b00000,0b00100,0b00100,0b00100,0b10101,0b01110,0b00100,0b00000};
    static char bigRight_[8] = {0b01000,0b01100,0b01110,0b01111,0b01110,0b01100,0b01000,0b00000};
    static char bigLeft_[8]  = {0b00010,0b00110,0b01110,0b11110,0b01110,0b00110,0b00010,0b00000};
    static char player_[8]   = {0b01110,0b01110,0b00100,0b11111,0b00100,0b01110,0b01010,0b01010};

    lcd.createChar(0, timer_);
    lcd.createChar(1, heart_);
    lcd.createChar(2, up_);
    lcd.createChar(3, down_);
    lcd.createChar(4, bigRight_);
    lcd.createChar(5, bigLeft_);
    lcd.createChar(6, player_);
}

// Show “Loading…”, then “Level X”, then “Go!”
void CustomCharDisplay::welcome() {
    lcd.locate(0, 0);
    lcd.printf("   Loading...   ");
    displayChar(3, 0, 1);  // spinner icon
    thread_sleep_for(500);

    for (int c = 10; c <= 12; ++c) {
        displayChar(10, c, 0);
        lcd.locate(c, 0);
        lcd.printf(".");
        thread_sleep_for(200);
    }

    lcd.cls();
    lcd.locate(4, 0);
    lcd.printf(" Level %d ", Player::level);
    thread_sleep_for(1000);

    lcd.cls();
    lcd.locate(5, 0);
    lcd.printf("  Go!  ");
    thread_sleep_for(500);
    lcd.cls();
}

// Draw big arrows, timer icon, score bar, monsters, player icon
void CustomCharDisplay::defaultDisplay() {
    // Arrows
    displayChar(4, 0, 0);
    displayChar(4, 1, 0);
    displayChar(5, 3, 0);
    displayChar(5, 4, 0);

    // Timer
    displayChar(0, 6, 0);

    // Score & monsters
    scoreUpdate();
    updateMonsters();

    // Player
    displayChar(6, 0, 1);
}

// Clear old & draw up to three pixels for Player::score
void CustomCharDisplay::scoreUpdate() {
    // Clear
    displayChar(10, 15, 0);
    displayChar(10, 14, 0);
    displayChar(10, 13, 0);

    int pts = Player::score;
    if (pts > 0) displayChar(10, 15, 0);
    if (pts > 1) displayChar(10, 14, 0);
    if (pts > 2) displayChar(10, 13, 0);
}

// Draw one monster icon (slot 3) per mistake on row 1
void CustomCharDisplay::updateMonsters() {
    for (int i = 0; i < Player::monsterNum; ++i) {
        displayChar(3, i, 1);
    }
}
