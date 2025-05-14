#include "mbed.h"
#include "buttons.h"

Button::Button(PinName pin, void (*cb)())
    : btn(pin), sem(0, 1), callback(cb)
{
    btn.mode(PullUp);
    btn.fall([this]() {
        sem.release();
    });
    thread.start([this]() {
        while (true) {
            sem.acquire();
            ThisThread::sleep_for(50ms);
            if (callback) {
                callback();
            }
        }
    });
}

void Button::init() {
    // Optionally implement further initialization
}

void Button::clearInterrupt() {
    // Optionally implement interrupt clearing
}

void Button::debounce() {
    // Optionally implement debounce logic
}
