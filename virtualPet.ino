
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
#include "Pet.h"

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);     // tell the RedBoard what pins are connected to the display

int buttonPin = 2;                    //pin that the button is connected to
int buzzerPin = 6;                    //pin for driving the buzzer
int buttonPressTime = 0;              //variable to show how much time the player has left to guess the word (and press the button)

long timeLimit = 15000;               //time limit for the player to guess each word
long startTime = 0;                   //used to measure time that has passed for each word
int roundNumber = 0;                        //keeps track of the roundNumber so that it can be displayed at the end of the game
const int arraySize = 3;


const char* options[arraySize] = {"Display Your Pet", "Feed your Pet", "Play Time"};

// the start value in the sequence array must have a value that could never be an index of an array
// or at least a value outside the range of 0 to the size of the words array - 1; in this case, it can't be between 0 to 24
int sequence[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; //start with an array full of -1's

void setup() {

  pinMode(buttonPin, INPUT_PULLUP);       //set the button pin as an input

  lcd.begin(16, 2);                       //tell the LCD library the size of the screen

  //showStartSequence();                    //print the start sequence text

}

void loop() {
    lcd.print(pet.getName());
    delay(8000);
    int result = get_Menu_Options();
    lcd.clear();
    lcd.print("results are in ");

    const int DETAILS = 0;
    const int FEED = 1;
    const int CUDDLE = 2;
    const int PLAY = 3;

    switch (result)
    {
    case DETAILS:
        showPetDetails();
        break;
    case FEED:
        feedPet();
        break;
    case CUDDLE:
        PlayWithPet();
        break;
    
    default:
        break;
    }
        delay(10000);

}

void showPetDetails()
{
  lcd.clear();
  lcd.print("Pet Details");
}

void feedPet()
{
  lcd.clear();
  lcd.print("Feeding Pet");
}

void PlayWithPet()
{
  lcd.clear();
  lcd.print("Playing");
}


int get_Menu_Options()
{

  bool isButtonPressed = false;
  int optionIndex = 0;
  lcd.clear();   //clear the screen
  lcd.print("Press the button");   //Display Choose one of options then delay for 2 seconds 
  lcd.setCursor(0, 1);    
  lcd.print("for the option");
  delay(2000);
  while (!isButtonPressed){  
    
    startTime = millis();  //record the time that this option started
    while(millis() - startTime < timeLimit){ 
      lcd.clear();  //clear screen
      lcd.print(options[optionIndex]); // print option
      int roundedTime = round((timeLimit - (millis() - startTime)) / 1000); //calculate the time left in the round (dividing by 1000 converts the number to seconds
      lcd.setCursor(14, 1);                                                 //set the cursor in the lower right corner of the screen
      lcd.print("  ");
      lcd.setCursor(14, 1);   //set the cursor in the lower right corner of the screen
      lcd.print(roundedTime); //print the time left in the time limit
      delay(15);
      
      if (digitalRead(buttonPin) == LOW) {
        isButtonPressed = true;
        tone(buzzerPin, 272, 10);                   //emit a short beep when the button is pressed
        lcd.clear();
        lcd.print("Button Pressed");
        delay(10000); 
       //return user_Input to main program
      }
  
    }

    //change the option index to be next one and redo options if
    if(!isButtonPressed){
      if(optionIndex== (arraySize -1)){
      optionIndex = 0;
    }else{
      optionIndex+=1;
    }
      
    }

 }
 return optionIndex;
}

void feedOption()
{
  const char * foodOptions[] = {"Chicken","Apple","Carrot"};
  const int numberOfFoodOption = 3;
  bool isButtonPressed = false;
  int optionIndex = 0;
  lcd.clear();   //clear the screen
  lcd.print("Pick the food");   //Display Choose one of options then delay for 2 seconds 
  lcd.setCursor(0, 1);    
  lcd.print("to feed your pet");
  int i =0;
  int userChoice;
  delay(2000);
  while (!isButtonPressed){  
    
    startTime = millis();  //record the time that this option started
    while(millis() - startTime < timeLimit){ 
      lcd.clear();  //clear screen
      lcd.print("Option "); // write in the lcd screen option number
      lcd.print(i+1);
      lcd.setCursor(0, 1); 
      lcd.print(foodOptions[i]);
      int roundedTime = round((timeLimit - (millis() - startTime)) / 1000); //calculate the time left in the round (dividing by 1000 converts the number to seconds
      lcd.setCursor(14, 1);                                                 //set the cursor in the lower right corner of the screen
      lcd.print("  ");
      lcd.setCursor(14, 1);   //set the cursor in the lower right corner of the screen
      lcd.print(roundedTime); //print the time left in the time limit
      delay(1000);
      
      if (digitalRead(buttonPin) == LOW) {
        isButtonPressed = true;
        tone(buzzerPin, 272, 10);                   //emit a short beep when the button is pressed
        lcd.clear();
        lcd.print("You Selected");
        lcd.setCursor(0, 1); 
        lcd.print(foodOptions[i]);
        delay(3000); 
      }
 
  
    }

    //change the option index to be next one and redo options if
    if(!isButtonPressed){
      // change the index of the food 
      i = i+1;
      if(i== numberOfFoodOption){
        i=1;
      }
      
  }

 }
}

void showPetDisplays(){


//
//  lcd.clear();
//  lcd.print("Your pet's Name is ");
//  lcd.setCursor(1,1);
//  lcd.print(aPet.getName());
//  delay(2000);
//
//  
//  lcd.clear();
//  lcd.print("Your pet age is");
//  lcd.setCursor(1,1);
//  lcd.print(aPet.getAge() +" years old");
//  delay(5000);
//
//
//  lcd.clear();
//  lcd.print("Your pet weights");
//  lcd.setCursor(1,1);
//  lcd.print(pet.getWeight()+ " pounds");
//  delay(5000);
//
//
//
//  lcd.clear();
//  lcd.print("Your pet looks like the following");
//  lcd.setCursor(1,1);
//  lcd.print(pet.getImage());
//  delay(5000);

}


//--------------FUNCTIONS------------------------------

//DISPLAYS A COUNTDOWN TO START THE GAME
void showStartSequence() {

  lcd.clear();                  //clear the screen

  lcd.setCursor(0, 0);          //move the cursor to the top left corner
  lcd.print("Welcome to Virtual ");       //print "Welcome to Virtual"

  lcd.setCursor(0, 1);          //move the cursor to the bottom left corner
  lcd.print("Pet World");         //print "Pet World"

  delay(2000);                  //Wait 2 seconds

}
