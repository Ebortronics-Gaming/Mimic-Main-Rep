#include "mbed.h"
#include <stdio.h>
//Communciating what analogue pins the y value and the x value will be read from 
AnalogIn y(A0);
AnalogIn x(A1);
class joystick
{

//Defiining the array which will store the moves by the user 
uint8_t UserIn[4];
uint8_t array_index = 0;

//float values of the y value and x value from the joystick
    float y_val;
    float x_val;
// Thresholds (tune these based on testing)
#define JOY_CENTER 2048  // Middle of 12-bit ADC (range 0–4095)
#define THRESHOLD 1000
void storeplayermoves(float y_val,float x_val) 
     { 
        if (array_index >4 && y_val!=JOY_CENTER + THRESHOLD && x_val!=JOY_CENTER + THRESHOLD){
        thread_sleep_for(400);

        if (y_val > JOY_CENTER + THRESHOLD) {
            UserIn[array_index++] = 6;  // UP 
        } else if (y_val < JOY_CENTER - THRESHOLD) {
            UserIn[array_index++] = 7;  // DOWN
        } else if (x_val < JOY_CENTER - THRESHOLD) {
            UserIn[array_index++] = 8;  // LEFT
        } else if (x_val > JOY_CENTER + THRESHOLD) {
            UserIn[array_index++] = 9;  // RIGHT
        }
      }
     }
};

class joystick {};
