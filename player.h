#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

class Player {
public:
    static int score;
    static int level;
    static int arrowNum;
    static int monsterNum;

    static void reset();
    static void setLevel(int lvl);
    static void addScore(int pts = 1);
    static void addMonster();
    static bool isGameOver();
};

#endif // PLAYER_H
