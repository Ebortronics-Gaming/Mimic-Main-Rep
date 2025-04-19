#include "mbed.h"

class Button {
public:
    InterruptIn btn;      // the physical button
    Semaphore sem;        // semaphore signaled by interrupt
    Thread thread;        // thread that waits for button press
    void (*callback)();   // function to call when button is pressed

    
    Button(PinName pin, void (*cb)())       // constructor to initialize members using an initializer list
        : btn(pin),      // initialize btn with the parameter pin
          sem(0, 1),     // sem with an initial value 0 and a max of 1 token
          callback(cb)   // set the callback function.
    {
        
        btn.mode(PullUp);   // uses the internal pull up resistor

        
        
        btn.fall([this]() {     // attach an interrupt on the falling edge
            sem.release();      // lambda function captures "this" so it can call sem.release()
        });

        
        thread.start([this]() {     // starts thread that waits for the semaphore token
            while (true) {
                sem.acquire();              // wait for button press
                ThisThread::sleep_for(50ms);  // simple debounce delay (50ms)
                if (callback) {
                    callback();             // call the callback function
                }
            }
        });
    }
};

