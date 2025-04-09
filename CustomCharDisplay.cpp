// ------------------------------------------------------------------------------------
// Developed by Vishwa (Do not modify without prior discussion)
// Last Modified : 09 April 2025 by author 
// Please consult the original author before making any changes to ensure consistency.
// ------------------------------------------------------------------------------------

#include "CustomCharDisplay.h"

CustomCharDisplay::CustomCharDisplay(TextLCD &lcdRef) : lcd(lcdRef) {
    static char timer_[8] = {
            0b01110,
            0b11101,
            0b11011,
            0b11111,
            0b01110,
            0b00000,
            0b00000,
            0b00000
        };
        static char heart_[8] = {
            0b01010, 
            0b11111, 
            0b11111, 
            0b01110,
            0b00100, 
            0b00000, 
            0b00000, 
            0b00000
        };
        static char up_[8] = {
            0b00000, 
            0b00100, 
            0b01110, 
            0b10101,
            0b00100, 
            0b00100, 
            0b00100, 
            0b00000
        };
        static char down_[8] = {
            0b00000, 
            0b00100, 
            0b00100, 
            0b00100,
            0b10101, 
            0b01110, 
            0b00100, 
            0b00000
        };
        static char bigRight_[8] = {
            0b01000,
            0b01100,
            0b01110,
            0b01111,
            0b01110,
            0b01100,
            0b01000,
            0b00000
        };
        static char bigLeft_[8] = {
            0b00010,
            0b00110,
            0b01110,
            0b11110,
            0b01110,
            0b00110,
            0b00010,
            0b00000
        };
        static char player_[8] = {
            0b01110, 
            0b01110, 
            0b00100, 
            0b11111,
            0b00100, 
            0b01110, 
            0b01010, 
            0b01010
        };
        static char monster_[8] = {
            0b01110, 
            0b11111, 
            0b10101, 
            0b11111,
            0b11011, 
            0b10001, 
            0b11111, 
            0b10101
        };

        int timer = 0;
        int heart  = 1;
        int player = 2;
        int monster = 3;
        int bigRight = 4;
        int bigLeft = 5;
        int up = 6;
        int down = 7;

        lcd.writeCustomCharacter(timer_, 1);
        lcd.writeCustomCharacter(heart_, 2);
        lcd.writeCustomCharacter(player_, 3);
        lcd.writeCustomCharacter(monster_, 4);
        lcd.writeCustomCharacter(bigRight_, 5);
        lcd.writeCustomCharacter(bigLeft_, 6);
        lcd.writeCustomCharacter(up_, 7);
        lcd.writeCustomCharacter(down_, 8);
    }

    
void CustomCharDisplay::displayChar(int input, int col, int row) {
    lcd.locate(col, row);
    if (input >= 0 && input <= 7) {
        lcd.printf("%c", input); 
    } else if (input == 8) {
        lcd.printf("%c", 0b01111110); 
    } else if (input == 9) {
        lcd.printf("%c", 0b01111111); 
    } else if (input == 10) {
        lcd.printf("%c", 0b11111110); 
    } else {
        lcd.printf("?"); 
    }
}

void CustomCharDisplay::defaultDisplay() {
    displayChar(4, 0, 0);  // Big Arrows
    displayChar(4, 1, 0);  // Big Arrows
    displayChar(5, 3, 0);  // Big Arrows
    displayChar(5, 4, 0);  // Big Arrows
    displayChar(0, 6, 0);  // Clock icon (timer)
    displayChar(1, 12, 0); // Heart icon
    displayChar(2, 0, 1);  // Player icon
}

void CustomCharDisplay::scoreUpdate() {
    displayChar(10, 15, 0);
    displayChar(10, 14, 0);
    displayChar(10, 13, 0);
}
