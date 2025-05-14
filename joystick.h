#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "mbed.h"
#include <stdint.h>

#define MAX_JOYSTICK_MOVES 20

enum Direction {
    DIR_NONE = 0,
    DIR_UP = 6,
    DIR_DOWN = 7,
    DIR_LEFT = 8,
    DIR_RIGHT = 9
};

class Joystick {
public:
    Joystick(PinName xPin = A1, PinName yPin = A0);
    void begin();
    void update();
    void clearMoves();
    void getMoves(uint8_t* outArray, uint8_t &outCount) const;
    Direction readDirection();
private:
    AnalogIn  _xAxis, _yAxis;
    uint8_t   _moves[MAX_JOYSTICK_MOVES];
    uint8_t   _moveCount;
};

#endif // JOYSTICK_H
