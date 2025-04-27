#include "mbed.h"
#include <stdint.h>

// After 3 mistakes → game over
#define MONSTER_THRESHOLD 3

class Player {
public:
    // Static game state (read by CustomCharDisplay)
    static int score;
    static int level;
    static int arrowNum;    // how many inputs to expect each round
    static int monsterNum;  // mistakes so far

    // Reset for brand-new run
    static void reset() {
        score      = 0;
        level      = 1;
        arrowNum   = 4;   // start with 4 moves
        monsterNum = 0;
    }

    // Called once menu picks a level
    static void setLevel(int lvl) {
        level    = lvl;
        arrowNum = lvl + 3;  // e.g. level 1 → 4 inputs, level 2 → 5, etc.
    }

    // Award points for a correct sequence
    static void addScore(int pts = 1) {
        score += pts;
    }

    // Record a mistake
    static void addMonster() {
        monsterNum++;
    }

    // True if too many monsters
    static bool isGameOver() {
        return (monsterNum >= MONSTER_THRESHOLD);
    }
};

// Initialize static members
int Player::score      = 0;
int Player::level      = 1;
int Player::arrowNum   = 4;
int Player::monsterNum = 0;
