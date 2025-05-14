#include "player.h"

#define MONSTER_THRESHOLD 3

int Player::score      = 0;
int Player::level      = 1;
int Player::arrowNum   = 4;
int Player::monsterNum = 0;

void Player::reset() {
    score      = 0;
    level      = 1;
    arrowNum   = 4;
    monsterNum = 0;
}

void Player::setLevel(int lvl) {
    level    = lvl;
    arrowNum = lvl + 3;
}

void Player::addScore(int pts) {
    score += pts;
}

void Player::addMonster() {
    monsterNum++;
}

bool Player::isGameOver() {
    return (monsterNum >= MONSTER_THRESHOLD);
}
