#include "mbed.h"
#include "TextLCD_CC.h" 
#include "CustomCharDisplay.h"

bool difficultyPageFlag = false;

class displayClass : public CustomCharDisplay{
    private:
        int selectedCol = -1;
        Ticker arrowTicker;
        bool flashing = false;
    public:
        //Stores the level the player wants
        int level = 0;
        //Stores the menu Screen Option Selection (High Score, How To Play, Game Story, Settings)
        string currentSelection = "";
        //Stores either to display the sound or high score settings screen
        string selectedSetting = "";
        //Stores if the user wants the sound on or off
        string soundSetting = "";
        //Stores if the user wants to keep or reset their high score
        string highScoreSetting = "";
        
        //Displays Welcome message when console is powered on
        void displayWelcomeMessage(const char* msg) {
            int len = strlen(msg);
            int width = 16;
            int iconGap = 1;
            int numIcons = 4;
            

            for(int i = 0; i <= len + width ; i++){
                lcd.cls();
                lcd.locate(0,0);

                for(int j = 0; j < width; j++){
                    int index = i + j -(width - 1);
                    
                    if ((index >= 0) && (index < len)){
                        lcd.putc(msg[index]);
                    }
                    else{
                        lcd.putc(' ');
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
            lcd.cls();
        }

        void displayArrow(int col){ 
            displayChar(5,col,1);
        }

        void clearArrow(int col, int row){
            lcd.locate(col , row);
            lcd.putc(' ');
        }

        void flashArrowDifficulty(int col){
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

        //Displays Difficulty Page
        void displayDifficultyPage(){
            difficultyPageFlag = true;
            lcd.cls();

            lcd.locate(0,0);
            lcd.printf("Difficulty Page");

            lcd.locate(3,1);
            lcd.putc('1');

            lcd.locate(8,1);
            lcd.putc('2');

            lcd.locate(13,1);
            lcd.putc('3');

            while(true){
                if(b1 == 1) handleButtonPressDisplay(1,2);
                if(b2 == 1) handleButtonPressDisplay(2,7);
                if(b3 == 1) handleButtonPressDisplay(3,12);
                thread_sleep_for(100);
            }
        }

        //Callback Function for Button
        void handleButtonPressDisplay(int pressedLevel , int col){
            if (level == pressedLevel){
                arrowTicker.detach();
                lcd.cls();
                difficultyPageFlag = false;
                selectedCol = -1;
            }
            else{
                level = pressedLevel;
                selectedCol = col;
                flashing = false;
                arrowTicker.detach();

                lcd.locate(2,1);
                lcd.putc(' ');
                lcd.locate(7,1);
                lcd.putc(' ');
                lcd.locate(12,1);
                lcd.putc(' ');

                arrowTicker.attach(callback(this , &displayClass::flashArrowDifficulty), 500ms);
            }

            while(((pressedLevel == 1) && (b1 == 1)) || ((pressedLevel == 2) && (b2 == 1)) || ((pressedLevel == 3) && (b3 == 1))){
                thread_sleep_for(100);
            }
        }

        //Flashing an arrow char function
        flashArrow(int col, int row){
            while(true){
                displayChar(9,col,row);
                displayChar(10,col,row);
            }
        }

        //Displays home page screen
        void displayHomePage(){
            lcd.cls():
            lcd.locate(0,0);
            lcd.printf("MIMIC")
            lcd.locate(12,0);
            lcd.printf("Play");
            lcd.locate(12,1);
            lcd.printf("Menu");

            displayChar(1,5,0);
            displayChar(1,6,0);
            displayChar(1,7,0);

            displayChar(4,11,0);
            displayChar(4,1,1);
            displayChar(4,2,1);
            displayChar(4,3,1);
            displayChar(4,4,1);
            displayChar(4,11,1);

            displayChar(2,0,1);
            displayChar(3,5,1);
            displayChar(3,6,1);
            displayChar(3,7,1);

            flashArrow(10,0);

            while(true){
                if(joystick == "down"){
                    displayChar(10,10,0);
                    flashArrow(10,1);
                    if(joystick == "up"){
                        displayChar(10,10,1);
                        flashArrow(10,0);
                    }
                }
                
            }
        }

        //Displays menu screen
        void displayMenuScreen(){
            tempCurrentSelection = "";
            lcd.cls();
            while(true){ 
                lcd.locate(4,0);
                lcd.printf("High Score");
                flashArrow(3,0);
                tempCurrentSelection = "High Score";
                thread_sleep_for(200);

                if((joystick == "down") && (tempCurrentSelection == "High Score")){
                    lcd.printf("How To Play");  
                    tempCurrentSelection = "How To Play";  
                    thread_sleep_for(200);
                }

                if((joystick == "up") && (tempCurrentSelection == "How To Play")){
                    lcd.printf("High Score   ");  
                    tempCurrentSelection = "High Score";  
                    thread_sleep_for(200);
                }

                if((joystick == "down") && (tempCurrentSelection == "How To Play")){
                    lcd.printf("Game Story   ");  
                    tempCurrentSelection = "Game Story";  
                    thread_sleep_for(200);
                }

                if((joystick == "up") && (tempCurrentSelection == "Game Story")){
                    lcd.printf("How To Play   ");  
                    tempCurrentSelection = "How To Play"; 
                    thread_sleep_for(200); 
                }

                if((joystick == "down") && (tempCurrentSelection == "Game Story")){
                    lcd.printf("Settings     ");  
                    tempCurrentSelection = "Settings"; 
                    thread_sleep_for(200); 
                }

                if((joystick == "up") && (tempCurrentSelection == "Settings")){
                    lcd.printf("Game Story    ");  
                    tempCurrentSelection = "Game Story";
                    thread_sleep_for(200);  
                }

                if(b1 == 1){
                    currentSelection = tempCurrentSelection;
                    break;
                }
            }
        }
        //Displays High Score
        void displayHighScore(int score){
            lcd.cls();
            lcd.locate(1,0);
            lcd.printf("This is your");
            lcd.locate(1,1);
            lcd.printf("high score:");
            lcd.locate(12,1);
            lcd.printf("%d",score);
            thread_sleep_for(4000);
            lcd.cls();
        }

        //Displays the game instructions
        void displayInstructions(){
            lcd.cls();
            lcd.locate(1,0);
            printf("1.Select  Play");
            displayChar(4,10,0);
            lcd.locate(1,1);
            lcd.printf("2.Select an");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("appropriate");
            lcd.locate(3,1);
            lcd.printf("game level");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(1,0);
            lcd.printf("3.A sequence of");
            lcd.locate(3,1);
            lcd.printf("arrows will");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("be appeared on");
            lcd.locate(3,1);
            lcd.printf("the top");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("left corner of");
            lcd.locate(3,1);
            lcd.printf("the screen");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("once the game");
            lcd.locate(3,1);
            lcd.printf("starts.");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(1,0);
            lcd.printf("You have to");
            lcd.locate(3,1);
            lcd.printf("remember the");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("sequence of");
            lcd.locate(3,1);
            lcd.printf("arrows");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(1,0);
            lcd.printf("5.Then you have");
            lcd.locate(3,1);
            lcd.printf("to enter the");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("correct arrow");
            lcd.locate(3,1);
            lcd.printf("sequence by");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("using the joy");
            lcd.locate(3,1);
            lcd.printf("stick.");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(1,0);
            lcd.printf("6.If you enter");
            lcd.locate(3,1);
            lcd.printf("the correct");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("sequence of");
            lcd.locate(3,1);
            lcd.printf("arrows, your");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("score will be");
            lcd.locate(3,1);
            lcd.printf("increased");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(1,0);
            lcd.printf("7.If your arrow");
            lcd.locate(3,1);
            lcd.printf("sequence is");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("incorrect you");
            lcd.locate(3,1);
            lcd.printf("will not get");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("points and");
            lcd.locate(3,1);
            lcd.printf("the monsters");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("will get more");
            lcd.locate(3,1);
            lcd.printf("close to the");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("hero.");
            lcd.locate(1,1);
            lcd.printf("8.If monsters");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("get near the");
            lcd.locate(3,1);
            lcd.printf("hero you will");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("lose.");
            lcd.locate(1,1);
            lcd.printf("9.If you can");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("stay until");
            lcd.locate(3,1);
            lcd.printf("timer hits");
            thread_sleep_for(3000);
            lcd.cls();

            lcd.locate(3,0);
            lcd.printf("zero, you");
            lcd.locate(3,1);
            lcd.printf("will win");
            thread_sleep_for(3000);
            lcd.cls();
        }

        //Displays the game story
        void displayStory(){
            lcd.cls();
            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("This is year");
            lcd.locate(1,1);
            lcd.printf("3025. The world");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("is in danger!");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("Monsters came");
            lcd.locate(1,1);
            lcd.printf("to our planet");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("and started to");
            lcd.locate(1,1);
            lcd.printf("attack us...");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("We have to");
            lcd.locate(1,1);
            lcd.printf("fight back!");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(3,15,0);
            lcd.locate(1,0);
            lcd.printf("Ha...Ha...");
            lcd.locate(1,1);
            lcd.printf("We will destroy");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(3,15,0);
            lcd.locate(1,0);
            lcd.printf("your planet...");
            lcd.locate(1,1);
            lcd.printf("Ha...Ha...");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("We won't let");
            lcd.locate(1,1);
            lcd.printf("you do that...");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(3,15,0);
            lcd.locate(1,0);
            lcd.printf("Let's see...");
            lcd.locate(1,1);
            lcd.printf("Ha...Ha...");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);
            lcd.locate(1,0);
            lcd.printf("Let's save our");
            lcd.locate(1,1);
            lcd.printf("planet...");
            thread_sleep_for(3000);
            lcd.cls();

            displayChar(2,0,0);  displayChar(2,5,0);  displayChar(2,2,1);  displayChar(2,7,1);
            displayChar(2,1,0);  displayChar(2,6,0);  displayChar(2,3,1);
            displayChar(2,2,0);  displayChar(2,7,0);  displayChar(2,4,1);
            displayChar(2,3,0);  displayChar(2,0,1);  displayChar(2,5,1);
            displayChar(2,4,0);  displayChar(2,1,1);  displayChar(2,6,1);

            displayChar(3,8,0);  displayChar(3,13,0);  displayChar(3,10,1);  displayChar(3,15,1);
            displayChar(3,9,0);  displayChar(3,14,0);  displayChar(3,11,1);
            displayChar(3,10,0);  displayChar(3,15,0);  displayChar(3,12,1);
            displayChar(3,11,0);  displayChar(3,8,1);  displayChar(3,13,1);
            displayChar(3,12,0);  displayChar(3,9,1);  displayChar(3,14,1);
        }

        //Displays the setting page
        void displaySettings(){
            lcd.cls();
            lcd.locate(4,0);
            lcd.printf("Sound");
            lcd.locate(4,1);
            lcd.printf("High Score");
            displayChar(4,3,0);
            displayChar(4,3,1);
            flashArrow(2,0);
            tempSelectedSetting = "Sound";
            while(true){
                if((joystick == "down") && (tempSelectedSetting == "Sound")){
                    displayChar(10,2,0);
                    flashArrow(2,1);
                    tempSelectedSetting = "High Score";
                }

                if((joystick == "up") && (tempSelectedSetting == "High Score")){
                    displayChar(10,2,1);
                    flashArrow(2,0);
                }

                if(b1 == 1){
                    selectedSetting = tempSelectedSetting;
                    break;
                }
            }
        }

        //Displays the sound settings page
        void displaySoundScreen(){
            string tempSoundSetting = "";
            lcd.cls();
            lcd.locate(0,0);
            lcd.printf("Sound");
            lcd.locate(4,1);
            lcd.printf("On");
            lcd.locate(11,1);
            lcd.printf("Off");

            flashArrow(3,1);
            tempSoundSetting = "On";

            while(true){
                if((joystick == "right") && (soundSetting == "On")){
                    displayChar(10,3,1);
                    flashArrow(9,1);
                    tempSoundSetting = "Off";
                }

                if((joystick == "left") && (soundSetting == "Off")){
                    displayChar(10,9,1);
                    flashArrow(3,1);
                    tempSoundSetting = "On";
                }

                if(b1 == 1){
                    SoundSetting = tempSoundSetting;
                    break;
                }
            }
        }

        //Displays the high score settings page
        void displayHighScoreSettings(){
            string tempHighScoreSetting = "";
            lcd.locate(0,0);
            lcd.printf("High Score");
            lcd.locate(3,1);
            lcd.printf("Reset");
            lcd.locate(12,1);
            lcd.printf("Keep");
            displayChar(4,2,1);
            displayChar(4,11,1);

            flashArrow(10,1);
            tempHighScoreSetting = "Keep";

            while(true){
                if((joystick == "left") && (highScoreSetting == "Keep")){
                    displayChar(10,10,1);
                    flashArrow(1,1);
                    tempHighScoreSetting = "Reset";
                }

                if((joystick == "right") && (soundSetting == "Reset")){
                    displayChar(10,1,1);
                    flashArrow(10,1);
                    tempHighScoreSetting = "Keep";
                }

                if(b1 == 1){
                    highScoreSetting = tempHighScoreSetting;
                    break;
                }
            }
        }
};
