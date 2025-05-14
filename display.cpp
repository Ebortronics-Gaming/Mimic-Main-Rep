#include "display.h"
#include <cstring>

bool difficultyPageFlag = false;

display::display(TextLCD &lcdRef, PinName btnHome, PinName btnBack, PinName btnEnter)
    : CustomCharDisplay(lcdRef), selectedCol(-1), flashing(false), level(1),
      currentSelection("Play"), selectedSetting("Sound"), soundSetting("On"), highScoreSetting("Keep")
{
}

void display::begin() {
    cls();
}

void display::flashArrow(int id, int row) {
       displayChar(id, 7, row); // or whatever col/row you want
       thread_sleep_for(300);
       locate(7, row);
       putc(' ');
   }

void display::displayWelcomeMessage(const char* msg) {
    int len = 0;
    while (msg[len] != '\0') ++len;
    int width = 16;
    int iconGap = 1;
    int numIcons = 4;
    for(int i = 0; i <= len + width ; i++){
        cls();
        locate(0,0);
        for(int j = 0; j < width; j++){
            int index = i + j -(width - 1);
            if ((index >= 0) && (index < len)){
                putc(msg[index]);
            }
            else{
                putc(' ');
            }
        }
        for (int k = 0; k< numIcons; k++){
            int icon = (k==0) ? 2:3;
            int col = i - (numIcons-1-k)*(iconGap+1);
            if ((col >= 0) && (col < width)){
                displayChar(icon, col, 1);
            }
        }
        thread_sleep_for(300);
    }
    cls();
}

void display::displayArrow(int col){
    displayChar(5,col,1);
}

void display::clearArrow(int col, int row){
    locate(col , row);
    putc(' ');
}

void display::flashArrowDifficulty(int col){
    if ((level != 0) && (selectedCol != -1)){
        if (flashing){
            clearArrow(selectedCol , 1);
        }
        else {
            displayArrow(selectedCol);
        }
        flashing = !flashing;
    }
}

void display::displayMenuScreen(Joystick &stick,
                                volatile bool &enterPressed,
                                volatile bool &homePressed,
                                volatile bool &backPressed)
{
    const char* menu[] = {"Play","High Score","How To Play","Story","Settings"};
    int sel = 0;
    // Loop until ENTER, HOME or BACK
    while (!enterPressed && !homePressed && !backPressed) {
        cls();
        for (int i = 0; i < 5; i++) {
            locate(0,i);
            putc( i==sel ? '>' : ' ' );
            printf("%s",menu[i]);
        }
        ThisThread::sleep_for(100);
        Direction d = stick.readDirection();
        if (d==DIR_DOWN) sel=(sel+1)%5;
        if (d==DIR_UP)   sel=(sel+4)%5;
    }
    currentSelection = menu[sel];
}

void display::displayDifficultyPage(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed) {
    int selected = 1;
    while (!enterPressed && !backPressed && !homePressed) {
        cls();
        locate(0,0); printf("Select Difficulty");
        for (int i = 1; i <= 3; ++i) {
            locate(4*i,1);
            if (i == selected) printf("[%d]", i);
            else printf(" %d ", i);
        }
        ThisThread::sleep_for(150);
        Direction dir = stick.readDirection();
        if (dir == DIR_RIGHT && selected < 3) selected++;
        else if (dir == DIR_LEFT && selected > 1) selected--;
    }
    level = selected;
}

void display::displayHighScore(int score){
    cls();
    locate(1,0);
    printf("This is your");
    locate(1,1);
    printf("high score:");
    locate(12,1);
    printf("%d",score);
    thread_sleep_for(4000);
    cls();
}

void display::displayInstructions(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed) {
    const char* pages[] = {
        "1.Select  Play\n2.Select an",
        "appropriate\ngame level",
        "3.A sequence of\narrows will",
        "be appeared on\nthe top",
        "left corner of\nthe screen",
        "once the game\nstarts.",
        "You have to\nremember the",
        "sequence of\narrows",
        "5.Then you have\nto enter the",
        "correct arrow\nsequence by",
        "using the joy\nstick.",
        "6.If you enter\nthe correct",
        "sequence of\narrows, your",
        "score will be\nincreased",
        "7.If your arrow\nsequence is",
        "incorrect you\nwill not get",
        "points and\nthe monsters",
        "will get more\nclose to the",
        "hero.\n8.If monsters",
        "get near the\nhero you will",
        "lose.\n9.If you can",
        "stay until\ntimer hits",
        "zero, you\nwill win"
    };
    int numPages = sizeof(pages)/sizeof(pages[0]);
    int page = 0;
    while (!enterPressed && !backPressed && !homePressed) {
        cls();
        locate(0,0);
        printf("%s", pages[page]);
        ThisThread::sleep_for(200);
        Direction dir = stick.readDirection();
        if (dir == DIR_RIGHT && page < numPages-1) page++;
        else if (dir == DIR_LEFT && page > 0) page--;
    }
}

void display::displayStory(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed) {
    const char* pages[] = {
        "This is year\n3025. The world",
        "is in danger!\nMonsters came",
        "to our planet\nand started to",
        "attack us...\nWe have to",
        "fight back!\nHa...Ha...",
        "We will destroy\nyour planet...",
        "Ha...Ha...\nWe won't let",
        "you do that...\nLet's see...",
        "Ha...Ha...\nLet's save our",
        "planet..."
    };
    int numPages = sizeof(pages)/sizeof(pages[0]);
    int page = 0;
    while (!enterPressed && !backPressed && !homePressed) {
        cls();
        locate(0,0);
        printf("%s", pages[page]);
        ThisThread::sleep_for(200);
        Direction dir = stick.readDirection();
        if (dir == DIR_RIGHT && page < numPages-1) page++;
        else if (dir == DIR_LEFT && page > 0) page--;
    }
}

void display::displaySettings(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed) {
    const char* settings[] = {"Sound", "High Score"};
    int numSettings = 2;
    int selected = 0;
    while (!enterPressed && !backPressed && !homePressed) {
        cls();
        for (int i = 0; i < numSettings; ++i) {
            locate(0, i);
            if (i == selected) printf(">");
            else printf(" ");
            printf("%s", settings[i]);
        }
        ThisThread::sleep_for(150);
        Direction dir = stick.readDirection();
        if (dir == DIR_DOWN) selected = (selected + 1) % numSettings;
        else if (dir == DIR_UP) selected = (selected - 1 + numSettings) % numSettings;
    }
    selectedSetting = settings[selected];
    if (selectedSetting == "Sound") {
        displaySoundScreen(stick, enterPressed, backPressed, homePressed);
    } else if (selectedSetting == "High Score") {
        displayHighScoreSettings(stick, enterPressed, backPressed, homePressed);
    }
}

void display::displaySoundScreen(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed) {
    const char* options[] = {"On", "Off"};
    int selected = (soundSetting == "On") ? 0 : 1;
    while (!enterPressed && !backPressed && !homePressed) {
        cls();
        locate(0,0); printf("Sound");
        for (int i = 0; i < 2; ++i) {
            locate(4*i,1);
            if (i == selected) printf("[%s]", options[i]);
            else printf(" %s ", options[i]);
        }
        ThisThread::sleep_for(150);
        Direction dir = stick.readDirection();
        if (dir == DIR_RIGHT && selected < 1) selected++;
        else if (dir == DIR_LEFT && selected > 0) selected--;
    }
    soundSetting = options[selected];
}

void display::displayHighScoreSettings(Joystick &stick, volatile bool &enterPressed, volatile bool &backPressed, volatile bool &homePressed) {
    const char* options[] = {"Reset", "Keep"};
    int selected = (highScoreSetting == "Keep") ? 1 : 0;
    while (!enterPressed && !backPressed && !homePressed) {
        cls();
        locate(0,0); printf("High Score");
        for (int i = 0; i < 2; ++i) {
            locate(4*i,1);
            if (i == selected) printf("[%s]", options[i]);
            else printf(" %s ", options[i]);
        }
        ThisThread::sleep_for(150);
        Direction dir = stick.readDirection();
        if (dir == DIR_RIGHT && selected < 1) selected++;
        else if (dir == DIR_LEFT && selected > 0) selected--;
    }
    highScoreSetting = options[selected];
}

void display::defaultDisplay(){
    CustomCharDisplay::defaultDisplay();
}

void display::scoreUpdate(){
    CustomCharDisplay::scoreUpdate();
}

void display::updateMonsters(){
    CustomCharDisplay::updateMonsters();
}

void display::displayGameOverScreen(int monsterNum) {
    cls();
    locate(0,0);
    printf("GAME OVER");
    locate(0,1);
    printf("Monsters: %d", monsterNum);
    thread_sleep_for(3000);
    cls();
}

void display::displayWinScreen(int score) {
    cls();
    locate(0,0);
    printf("YOU WIN!");
    locate(0,1);
    printf("Score: %d", score);
    thread_sleep_for(3000);
    cls();
}
