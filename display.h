#ifndef DISPLAY_H
#define DISPLAY_H

#include "CustomCharDisplay.h"
#include "mbed.h"
#include <string>
#include "joystick.h"

class display : public CustomCharDisplay {
public:
    display(TextLCD &lcdRef, PinName btnHome, PinName btnBack, PinName btnEnter);
    void begin();
    void displayWelcomeMessage(const char* msg);
    void displayHomePage();
    void displayMenuScreen(Joystick &stick, volatile bool &enterPressed, volatile bool &homePressed, volatile bool &backPressed);
    void displayHighScore(int score);
    void displayInstructions(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed);
    void displayStory(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed);
    void displaySettings(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed);
    void displaySoundScreen(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed);
    void displayHighScoreSettings(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed);
    void displayDifficultyPage(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed);
    void defaultDisplay();
    void scoreUpdate();
    void updateMonsters();
    void flashArrow(int col, int row);
    void displayGameOverScreen(int monsterNum);
    void displayWinScreen(int score);
    int level;
    std::string currentSelection;
    std::string selectedSetting;
    std::string soundSetting;
    std::string highScoreSetting;
    int selectedCol;
    Ticker arrowTicker;
    bool flashing;
    void displayArrow(int col);
    void clearArrow(int col, int row);
    void flashArrowDifficulty(int col);
    void handleButtonPressDisplay(int pressedLevel, int col);
};

#endif // DISPLAY_H
