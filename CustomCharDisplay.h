// File: CustomCharDisplay.h

#ifndef CUSTOMCHARDISPLAY_H
#define CUSTOMCHARDISPLAY_H

#include "TextLCD_CC.h"
#include "player.cpp"   // to read Player::score and Player::monsterNum

/**
 * CustomCharDisplay
 * -----------------
 * Loads custom CGRAM characters, and renders the HUD:
 *   - Big arrows
 *   - Timer icon
 *   - Current score (3-pixel bar)
 *   - Monster icons (mistakes)
 *   - Player icon
 */
class CustomCharDisplay {
public:
    // Constructor: uploads all custom characters
    CustomCharDisplay(TextLCD &lcdRef);

    // Loading → “Level X” → “Go!” animation
    void welcome();

    // Draw big arrows, timer icon, score bar, monsters, player icon
    void defaultDisplay();

    // Update the three-pixel score at top-right
    void scoreUpdate();

    // Draw one monster icon per mistake on row 1
    void updateMonsters();

private:
    TextLCD &lcd;
};

#endif // CUSTOMCHARDISPLAY_H
