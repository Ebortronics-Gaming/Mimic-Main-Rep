#include "PatternGenerator.h"
#include <cstdlib>
#include <ctime>

PatternGenerator::PatternGenerator(CustomCharDisplay &dispRef) : display(dispRef), sequenceSize(0) {}

void PatternGenerator::pattern(int y) {
    sequenceSize = y;   

    for (int i = 0; i < y; i++) {
        srand(time(NULL));
        int num = (rand() % 4) + 6;
        sequence[i] = num;
        display.displayChar(num, 2, 0);
        thread_sleep_for(num*100);
        display.displayChar(10,2,0);
        thread_sleep_for(num*100);
    }
}

int* PatternGenerator::getSequence() {
    return sequence;
}

int PatternGenerator::getSequenceSize() {
    return sequenceSize;
}
