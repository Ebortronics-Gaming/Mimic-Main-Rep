#include "mbed.h"

class Player {
public:
   
    static int score; // global variables that are all static
    static int level;
    static int flashTime;

    
    static void addScore(int points) {  // adds the given points to the current score
        score += points;
    }
    
    static void setLevel(int lvl) { // sets the level and adjusts flashTime (future reference)
        level = lvl;

        if (level == 1) {
            flashTime = 800;
        } else if (level == 2) {
            flashTime = 600;
        } else if (level == 3) {
            flashTime = 400;
        } else if (level == 4) {
            flashTime = 200;
        }
    }

    static void NextLevel() {
        int newLevel; 
        if (level != 4) {
            int newLevel = level + 1;
        } else {
            int newLevel = 1;
        }
        setLevel(newLevel);
    }

    static void ResetLevel() {
        setLevel(1);
    }
};

int Player::score = 0;  // initialize static members with initial values
int Player::level = 1;
int Player::flashTime = 800;
