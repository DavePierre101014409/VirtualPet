/*
  SparkFun Inventor’s Kit
  Circuit 4C - Heads Up Game

  This is a DIY version of the popular Heads Up party game. To play, one person resets the RedBoard and holds the LCD
  facing away from them so that they cannot see it (usually on their forehead). The display will show a short countdown
  then display random words. The other player(s) who can see the screen must yell out clues until time runs out or the player
  guesses what word is on the screen. If they guess correctly, they can press the button on the breadboard and another word
  will be displayed.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>            //the liquid crystal library contains commands for printing to the display
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);     // tell the RedBoard what pins are connected to the display

int buttonPin = 2;                    //pin that the button is connected to
int buzzerPin = 6;                    //pin for driving the buzzer
int buttonPressTime = 0;              //variable to show how much time the player has left to guess the word (and press the button)

long timeLimit = 15000;               //time limit for the player to guess each word
long startTime = 0;                   //used to measure time that has passed for each word
int roundNumber = 0;                        //keeps track of the roundNumber so that it can be displayed at the end of the game
const int arraySize = 25;

const char* words[arraySize] = {"moose", "beaver", "bear", "goose", "dog", "cat", "squirrel", "bird", "elephant", "horse",
                                "bull", "giraffe", "seal", "bat", "skunk", "turtle", "whale", "rhino", "lion", "monkey",
                                "frog", "alligator", "kangaroo", "hippo", "rabbit"
                               };

// the start value in the sequence array must have a value that could never be an index of an array
// or at least a value outside the range of 0 to the size of the words array - 1; in this case, it can't be between 0 to 24
int sequence[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; //start with an array full of -1's

const char * image = "<--('')--->";

const char * name = "Lebron";
int age = 5;
int weight = 20;
bool hungry = true;


const char * isHungry()
{
     const char * response;
    if(hungry)
    {
        const char * response= " Your virtual pet is hungry!";
    }
    else
    {
        const char * response= " Your virtual pet is satisify!";
    }
    return response;
}


//--------------FUNCTIONS------------------------------

//DISPLAYS A COUNTDOWN TO START THE GAME
//TODO: finish during rockets game
void showStartSequence() {

  lcd.clear();                  //clear the screen

  lcd.setCursor(0, 0);          //move the cursor to the top left corner
  lcd.print("Welcome to ");       //print Welcome to 

  lcd.setCursor(0, 1);          //move the cursor to the bottom left corner
  lcd.print("Virtual Pet city");         //print Virtual Pet city

  delay(3000);                  //Wait 2 seconds

  lcd.clear();                  //clear the screen
  lcd.print("Get ready!");      //print "Get ready!"
  delay(1000);                  //wait 1 second

  lcd.clear();                  //clear the screen
  lcd.print("3");               //print "3"
  delay(1000);                  //wait 1 second

  lcd.clear();                  //clear the screen
  lcd.print("2");               //print "3"
  delay(1000);                  //wait 1 second

  lcd.clear();                  //clear the screen
  lcd.print("1");               //print "3"
  delay(1000);                  //wait 1 second
}


void feedPet(){
    //add text to make chop noise
    weight +=1;
    hungry = false;
}



void main(){

    const int DETAILS = 1;

    const int FEED = 2;
    const int WASHROOM = 3;
    const int PLAY = 4;

    int user_input = 0;


    switch (user_input)
    {
    case DETAILS:
       
        break;
    case FEED:
        /* code */
        break;
    case WASHROOM:
        /* code */
        break;
    
    default:
        break;
    }
}