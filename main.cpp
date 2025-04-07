#include "mbed.h"
#include "joystick.cpp"
#include "buttons.cpp"
#include "display.cpp"
#include "player.cpp"
#include "patterns.cpp"
#include <cstdio>
#include <limits>
#include <stdio.h>
#include <array>

Player player;

void btn1Action();
void btn2Action();
void btn3Action();

// Button objects with different pins & callbacks
Button btn1(D12, btn1Action);    // level changing button
Button btn2(D11, btn2Action);
Button btn3(D10, btn3Action);


int main() {

    while (true) { }
}


// Button Action Functions:
void btn1Action() {     // increases level
    printf("Button 1 is pressed\n");
    player.NextLevel();
}

void btn2Action() {
    printf("Button 2 is pressed\n");
    // to be continued...
}

void btn3Action() {
    printf("Button 3 is pressed\n");
    // to be continued...
}
