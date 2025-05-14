#include "CustomCharDisplay.h"
#include "mbed.h"
#include "player.h"
#include <cstdarg>

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

    lcd.writeCustomCharacter(timer_, 0);
    lcd.writeCustomCharacter(heart_, 1);
    lcd.writeCustomCharacter(up_, 2);
    lcd.writeCustomCharacter(down_, 3);
    lcd.writeCustomCharacter(bigRight_, 4);
    lcd.writeCustomCharacter(bigLeft_, 5);
    lcd.writeCustomCharacter(player_, 6);
}

void CustomCharDisplay::welcome() {
    lcd.locate(0, 0);
    lcd.printf("   Loading...   ");
    displayChar(3, 0, 1);
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

void CustomCharDisplay::defaultDisplay() {
    displayChar(4, 0, 0);
    displayChar(4, 1, 0);
    displayChar(5, 3, 0);
    displayChar(5, 4, 0);
    displayChar(0, 6, 0);
    scoreUpdate();
    updateMonsters();
    displayChar(6, 0, 1);
}

void CustomCharDisplay::scoreUpdate() {
    displayChar(10, 15, 0);
    displayChar(10, 14, 0);
    displayChar(10, 13, 0);
    int pts = Player::score;
    if (pts > 0) displayChar(10, 15, 0);
    if (pts > 1) displayChar(10, 14, 0);
    if (pts > 2) displayChar(10, 13, 0);
}

void CustomCharDisplay::updateMonsters() {
    for (int i = 0; i < Player::monsterNum; ++i) {
        displayChar(3, i, 1);
    }
}

void CustomCharDisplay::displayChar(int id, int col, int row) {
    lcd.locate(col, row);
    lcd.putc(id);
}

void CustomCharDisplay::cls() {
    lcd.cls();
}

void CustomCharDisplay::locate(int col, int row) {
    lcd.locate(col, row);
}

void CustomCharDisplay::putc(char c) {
    lcd.putc(c);
}

void CustomCharDisplay::printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    lcd.vprintf(fmt, args);
    va_end(args);
}
