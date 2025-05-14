#include "joystick.h"

#define JOY_CENTER        0.5f
#define JOY_THRESHOLD     0.15f

Joystick::Joystick(PinName xPin, PinName yPin)
    : _xAxis(xPin), _yAxis(yPin), _moveCount(0) {}

void Joystick::begin() {
    clearMoves();
}

void Joystick::update() {
    float x = _xAxis.read();
    float y = _yAxis.read();

    if (_moveCount < MAX_JOYSTICK_MOVES) {
        if      (y > JOY_CENTER + JOY_THRESHOLD)      _moves[_moveCount++] = DIR_UP;
        else if (y < JOY_CENTER - JOY_THRESHOLD)      _moves[_moveCount++] = DIR_DOWN;
        else if (x < JOY_CENTER - JOY_THRESHOLD)      _moves[_moveCount++] = DIR_LEFT;
        else if (x > JOY_CENTER + JOY_THRESHOLD)      _moves[_moveCount++] = DIR_RIGHT;
    }
}

void Joystick::clearMoves() {
    _moveCount = 0;
}

void Joystick::getMoves(uint8_t* outArray, uint8_t &outCount) const {
    outCount = _moveCount;
    for (uint8_t i = 0; i < _moveCount; ++i) {
        outArray[i] = _moves[i];
    }
}

Direction Joystick::readDirection() {
    float x = _xAxis.read();
    float y = _yAxis.read();
    if      (y > JOY_CENTER + JOY_THRESHOLD)      return DIR_UP;
    else if (y < JOY_CENTER - JOY_THRESHOLD)      return DIR_DOWN;
    else if (x < JOY_CENTER - JOY_THRESHOLD)      return DIR_LEFT;
    else if (x > JOY_CENTER + JOY_THRESHOLD)      return DIR_RIGHT;
    else                                          return DIR_NONE;
}
