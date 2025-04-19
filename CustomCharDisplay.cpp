// CustomCharDisplay.cpp
#include "CustomCharDisplay.h"
#include "player.cpp"
#include "mbed.h"

/// Constructor: loads all custom characters into CGRAM slots 1–8
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
    static char monster_[8]  = {0b01110,0b11111,0b10101,0b11111,0b11011,0b10001,0b11111,0b10101};

    // CGRAM: slot 1=timer, 2=heart, 3=player, 4=monster, 5=bigRight,
    //        6=bigLeft, 7=up, 8=down
    lcd.writeCustomCharacter(timer_,    1);
    lcd.writeCustomCharacter(heart_,    2);
    lcd.writeCustomCharacter(player_,   3);
    lcd.writeCustomCharacter(monster_,  4);
    lcd.writeCustomCharacter(bigRight_, 5);
    lcd.writeCustomCharacter(bigLeft_,  6);
    lcd.writeCustomCharacter(up_,       7);
    lcd.writeCustomCharacter(down_,     8);
}

/// Draw a custom character by index at (col,row).
/// input:
///   0 = timer, 1 = heart, 2 = player, 3 = monster,
///   4 = bigRight, 5 = bigLeft, 6 = up, 7 = down,
///   8 = left arrow, 9 = right arrow, 10 = blank
void CustomCharDisplay::displayChar(int input, int col, int row) {
    lcd.locate(col, row);
    if (input >= 0 && input <= 7) {
        // index 0–7 map directly to CGRAM slots 1–8
        lcd.printf("%c", input);
    }
    else if (input == 8) {
        lcd.printf("%c", 0b01111110);  // left arrow glyph
    }
    else if (input == 9) {
        lcd.printf("%c", 0b01111111);  // right arrow glyph
    }
    else if (input == 10) {
        lcd.printf("%c", 0b11111110);  // blank glyph
    }
    else {
        lcd.printf("?");               // out-of-range
    }
}

/// Render the default HUD:
///  • big arrows framing play area
///  • timer icon
///  • hearts (lives)
///  • monsters remaining
///  • player icon
void CustomCharDisplay::defaultDisplay() {
    // Big arrows
    displayChar(4, 0, 0);
    displayChar(4, 1, 0);
    displayChar(5, 3, 0);
    displayChar(5, 4, 0);

    // Timer icon
    displayChar(0, 6, 0);

    // Dynamic hearts & monsters
    updateLives();
    updateMonsters();

    // Player icon
    displayChar(2, 0, 1);
}

/// Update the score display (three pixels) at top‑right based on Player::score
void CustomCharDisplay::scoreUpdate() {
    displayChar(10, 15, 0);
    displayChar(10, 14, 0);
    displayChar(10, 13, 0);
}

/// Show loading animation, then "Level X" and "Go"
void CustomCharDisplay::welcome() {
    // Loading...
    lcd.locate(0, 0);
    lcd.printf("   Loading...   ");
    displayChar(3, 0, 1);  // monster icon as spinner
    thread_sleep_for(500);

    // Dot animation at cols 10→12
    for (int c = 10; c <= 12; ++c) {
        displayChar(10, c, 0);
        lcd.locate(c, 0);
        lcd.printf(".");
        thread_sleep_for(200);
    }

    // Clear & show Level X
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("    Level %d    ", Player::level);
    thread_sleep_for(1000);

    // Show "Go"
    lcd.locate(0, 0);
    lcd.printf("       Go       ");
    thread_sleep_for(1000);
}

/// Draw one heart per life starting at col 12, row 0
void CustomCharDisplay::updateLives() {
    for (int i = 0; i < Player::hearts; ++i) {
        displayChar(1, 12 + i, 0);
    }
}

/// Draw one monster icon per remaining monster on row 1
void CustomCharDisplay::updateMonsters() {
    for (int i = 0; i < Player::monsterNum; ++i) {
        displayChar(3, i, 1);
    }
}
