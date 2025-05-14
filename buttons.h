#ifndef BUTTONS_H
#define BUTTONS_H

#include "mbed.h"

class Button {
public:
    Button(PinName pin, void (*cb)());
    void init();
    void clearInterrupt();
    void debounce();
private:
    InterruptIn btn;
    Semaphore sem;
    Thread thread;
    void (*callback)();
};

#endif // BUTTONS_H
