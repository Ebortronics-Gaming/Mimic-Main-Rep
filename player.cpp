#include "mbed.h"

class Player {
public:
   
    static int score; // global variables that are all static
    static int level;
    static int flashTime;
    static int arrowNum;
    static int monsterNum;
    static int countdown;   // in seconds (600s = 10 mins)
    static int hearts;

    
    static void addScore(int points) {  // adds the given points to the current score
        score += points;
    }
    
    static void setLevel(int lvl) { // sets the level and adjusts flashTime (future reference)
        level = lvl;

        if (level == 1) {
            flashTime = 800;
            arrowNum = 4;
            monsterNum = 4;
        } else if (level == 2) {
            flashTime = 600;
            arrowNum = 5;
            monsterNum = 5;
        } else if (level == 3) {
            flashTime = 400;
            arrowNum = 6;
            monsterNum = 6;
        } else if (level == 4) {
            flashTime = 200;
            arrowNum = 7;
            monsterNum = 7;
        }
    }

    static void nextLevel() {
        int newLevel; 
        if (level != 4) {
            int newLevel = level + 1;
        } else {
            int newLevel = 1;
            gameOver(1);
        }
        setLevel(newLevel);
    }

    static void ResetLevel() {
        setLevel(1);
    }

    static void minusMonster() {
        if ((monsterNum = 1) && (level = 4)) {
            gameOver(1);
        } else if ((monsterNum = 1) && (level != 4)) {
            nextLevel();
        } else if (monsterNum != 1) {
            monsterNum -= 1;
        }
    }

    static void gameOver(int i) {
        ResetLevel();
        score = 0;
        hearts = 3;
        if (i) {
            printf("You win!!");
        } else {
            printf("You lose!!");
        }
    }

    static void minusHearts() {
        if (hearts != 1) {
            hearts -= 1;
        } else {
            gameOver(0);
        }
    }

};

int Player::score = 0;  // initialize static members with initial values
int Player::level = 1;
int Player::flashTime = 800;
int Player::arrowNum = 4;
int Player::countdown = 600;
int Player::monsterNum = 4;
int Player::hearts = 3;
