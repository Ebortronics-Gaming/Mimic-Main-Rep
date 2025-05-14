#include "TextLCD_CC.h"

TextLCD::TextLCD(PinName rs, PinName e, PinName d4, PinName d5, PinName d6, PinName d7, LCDType type)
    : _rs(rs), _e(e), _d(d4, d5, d6, d7), _type(type), _column(0), _row(0) {
    
    wait_us(20000);  // Wait for power-up
    
    // Function set
    writeCommand(0x33);
    writeCommand(0x32);
    writeCommand(0x28); // 4-bit mode, 2 lines
    
    // Display control
    writeCommand(0x0C); // Display ON, cursor OFF, blink OFF
    
    // Entry mode set
    writeCommand(0x06); // Increment cursor, no display shift
    
    cls(); // Clear display
}

void TextLCD::cls() {
    writeCommand(0x01); // Clear display
    wait_us(1640);     // Longer delay needed
    _column = 0;
    _row = 0;
}

void TextLCD::locate(int column, int row) {
    _column = column;
    _row = row;
    writeCommand(address(column, row));
}

void TextLCD::writeCustomCharacter(char custom[8], int index) {
    // Set CGRAM address
    writeCommand(0x40 + ((index - 1) * 8));
    
    // Write character data
    for (int i = 0; i < 8; i++) {
        writeData(custom[i]);
    }
    
    // Reset address to DDRAM
    writeCommand(0x80);
}

int TextLCD::_putc(int value) {
    writeData(value);
    return value;
}

int TextLCD::_getc() {
    return -1; // Not implemented
}
    
int TextLCD::rows() {
    switch (_type) {
        case LCD20x4:
            return 4;
        default:
            return 2;
    }
}

int TextLCD::columns() {
    switch (_type) {
        case LCD20x2:
        case LCD20x4:
            return 20;
        default:
            return 16;
    }
}

int TextLCD::address(int column, int row) {
    switch (_type) {
        case LCD20x4:
            switch (row) {
                case 0:
                    return 0x80 + column;
                case 1:
                    return 0xC0 + column;
                case 2:
                    return 0x94 + column;
                case 3:
                    return 0xD4 + column;
            }
        case LCD16x2:
        case LCD16x2B:
        case LCD20x2:
        default:
            return 0x80 + (row * 0x40) + column;
    }
}

void TextLCD::writeByte(int value) {
    _d = value >> 4;
    wait_us(1);
    _e = 1;
    wait_us(1);
    _e = 0;
    wait_us(1);
    
    _d = value & 0x0F;
    wait_us(1);
    _e = 1;
    wait_us(1);
    _e = 0;
    wait_us(1);
    
    wait_us(40); // Most instructions take 40us
}

void TextLCD::writeCommand(int command) {
    _rs = 0;
    writeByte(command);
}

void TextLCD::writeData(int data) {
    _rs = 1;
    writeByte(data);
    _column++;
}
