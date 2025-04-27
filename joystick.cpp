#include "mbed.h"
#include <stdint.h>

// Adjust these after testing on your joystick
#define JOY_CENTER        0.5f
#define JOY_THRESHOLD     0.15f
#define MAX_JOYSTICK_MOVES 20

class joystick {
public:
    // ctor: default X = A1, Y = A0
    joystick(PinName xPin = A1, PinName yPin = A0)
      : _xAxis(xPin), _yAxis(yPin), _moveCount(0) {}

    // Initialize / reset the buffer
    void begin() {
        clearMoves();
    }

    // Call periodically; if moved past threshold, record one direction
    void update() {
        float x = _xAxis.read();
        float y = _yAxis.read();

        if (_moveCount < MAX_JOYSTICK_MOVES) {
            if      (y > JOY_CENTER + JOY_THRESHOLD)      _moves[_moveCount++] = 6; // UP
            else if (y < JOY_CENTER - JOY_THRESHOLD)      _moves[_moveCount++] = 7; // DOWN
            else if (x < JOY_CENTER - JOY_THRESHOLD)      _moves[_moveCount++] = 8; // LEFT
            else if (x > JOY_CENTER + JOY_THRESHOLD)      _moves[_moveCount++] = 9; // RIGHT
        }
    }

    // Erase all recorded moves
    void clearMoves() {
        _moveCount = 0;
    }

    // Copy out current buffer and count
    void getMoves(uint8_t* outArray, uint8_t &outCount) const {
        outCount = _moveCount;
        for (uint8_t i = 0; i < _moveCount; ++i) {
            outArray[i] = _moves[i];
        }
    }

private:
    AnalogIn  _xAxis, _yAxis;
    uint8_t   _moves[MAX_JOYSTICK_MOVES];
    uint8_t   _moveCount;
};
