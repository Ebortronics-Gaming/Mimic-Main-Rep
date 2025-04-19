// CustomCharDisplay.h
#ifndef CUSTOMCHARDISPLAY_H
#define CUSTOMCHARDISPLAY_H

#include "TextLCD_CC.h"
#include "player.cpp"   // Access Player::hearts, Player::monsterNum, Player::level

/**
 * CustomCharDisplay
 * -----------------
 * Manages loading and drawing of custom characters,
 * and renders HUD elements (lives, monsters, timer, score, etc.)
 * based on the Player class state.
 */
class CustomCharDisplay {
public:
    /// Constructor: pass in your TextLCD instance
    CustomCharDisplay(TextLCD &lcdRef);

    /**
     * Draw a custom character by index at (col, row).
     * input:
     *   0 = timer
     *   1 = heart
     *   2 = player
     *   3 = monster
     *   4 = bigRight
     *   5 = bigLeft
     *   6 = up
     *   7 = down
     *   8 = left arrow
     *   9 = right arrow
     *  10 = blank
     */
    void displayChar(int input, int col, int row);

    /**
     * Render the default game HUD:
     *   • big arrows framing play area
     *   • timer icon
     *   • hearts (lives)
     *   • monsters
     *   • player icon
     */
    void defaultDisplay();

    /// Update the score display at top‑right using Player::score
    void scoreUpdate();

    /**
     * Show loading/welcome animation,
     * then dynamically display "Level X" (Player::level), then "Go"
     */
    void welcome();

    /// Draw hearts based on Player::hearts
    void updateLives();

    /// Draw monsters based on Player::monsterNum
    void updateMonsters();

private:
    TextLCD &lcd;
};

#endif // CUSTOMCHARDISPLAY_H
