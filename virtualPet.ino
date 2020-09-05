
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
Pet pet;


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

//This method will  receive input from the computer and create a pet object with it 
void createPet()
{
    // Serial.println("Please enter the name for your pet");   
  
    // if (Serial.available() > 0)
    // {                               
    //     const char * name = Serial.readString(); 

    //     pet.setName(name);
    //     Serial.print("Yor pet's name is "); //print the pet name  to user
    //     Serial.println(name);
    //     delay(3000);
    // }
    // Serial.println("Please enter the image that you would like your pet to look like. (Less then 16 chracters)");   
    // String image;
    // if (Serial.available() > 0)
    // {                                           
    //     image = Serial.readString();             
    //     Serial.print("Yor pet looks like this"); // print the image 
    //     Serial.println(image);
    //     delay(3000);
    // }

    Serial.println("Please enter a number for your pet's weight in pounds");
    if (Serial.available() > 0)
    {                                   
        int weight = Serial.parseInt(); 
        pet.setWeight(weight);
        Serial.print("Yor Pet weight is "); 
        Serial.print(weight);
        Serial.println("pounds");
    }

    Serial.println("Please enter a number for your pet's age in years");
    if (Serial.available() > 0)
    {                               
        int age = Serial.parseInt(); 
        pet.setAge(age);
        Serial.print("Yor Pet age is ");
        Serial.print(age);
        Serial.println("years");
    }

    
    
   
}



//This method will run the game for our virtual pet
void runGame()
{

  //   note  frequency
  //   c     262 Hz
  //   d     294 Hz
  //   e     330 Hz
  //   f     349 Hz
  //   g     392 Hz
  //   a     440 Hz
  //   b     494 Hz
  //   C     523 Hz

  // took notes from the digital trumpet  circuit
  const int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
  const int numberOfNotes = 8;      // the number of different notes
  const int sizeOfSequence = 4;     // the number of notes we will run
  randomSeed(analogRead(0));        //reset the random seed
  int currentNoteIndex = 0;         //set the current note to intially be 0
  int noteSequence[sizeOfSequence]; // this array will contain the notes that will be played for each game

  // get 5 random notes that will be create a sequence
  for (int i = 0; i < sizeOfSequence; i++)
  {
    currentNoteIndex = random(0, numberOfNotes); // get a random value from 0 and 7 to be a index that represent a note
    noteSequence[i] = notes[currentNoteIndex];   //add the note in the note sequence
  }

  //This will play the song for a second a write the option on the screen
  int options[] = {1, 2, 3, 4, 5};
  long twoSecTimeLimit = 2000;
  lcd.clear();
  lcd.print("Playing Game");
  lcd.setCursor(0, 1);
  lcd.print("Now");
  delay(5000);
  for (int i = 0; i < sizeOfSequence; i++) // play each note in the seqeunece for two seconds
  {

    lcd.clear();
    lcd.print("Option "); // write in the lcd screen option number
    lcd.print(options[i]);
    lcd.print("  ");
    lcd.print(noteSequence[i]);
    tone(buzzerPin, noteSequence[i]); // play the buzzer
    delay(twoSecTimeLimit);           // delay for 2 second timeout
    noTone(buzzerPin);                // turn off the buzzer
    delay(twoSecTimeLimit);
  }

  //generate question and print it out
  int mutipleChoiceOptions[] = {-1, -1, -1, -1, -1}; // create an array of mutiple choice options
  randomSeed(analogRead(0));                         //reset the random seed (Arduino needs this to generate truly random numbers
  int answerNoteIndex = random(0, sizeOfSequence);   // generate a number from 0-4
  int answerNote = noteSequence[answerNoteIndex];
  long fiveSecTimeOut = 5000;
  lcd.clear();
  lcd.print("Which note play"); // print on the lcd screen the question : "Which note played at A"
  lcd.setCursor(0, 1);
  lcd.print("at Option ");
  lcd.print(options[answerNoteIndex]);
  delay(fiveSecTimeOut);

  //Create 5 different mutiple choice options

  bool containAnswer = false;
  for (int i = 0; i < sizeOfSequence; i++)
  { //do this until all 5 postions are filled

    int currentNote = 0;      //variable to hold the current number
    boolean hasMatch = false; //does the currentNumber match any of the previous numbers?

    //generate random numbers until you've generated one that doesn't match any of the other numbers in the array
    do
    {
      currentNote = notes[random(0, numberOfNotes)]; //generate a random number from 0 to 7
      hasMatch = false;                              //we haven't checked for matches yet, so start by assuming that it doesn't match
      for (int i = 0; i < sizeOfSequence; i++)
      { //for all 5 numbers in the array
        if (currentNote == mutipleChoiceOptions[i])
        {                  //does the currentNote match any of the numbers?
          hasMatch = true; //if so, set the match variable to true
        }
        if (mutipleChoiceOptions[i] == answerNote)
        {
          containAnswer = true;
        }
      }
    } while (hasMatch == true);            //if the match variable is true, generate another random number and try again
    mutipleChoiceOptions[i] = currentNote; //if the match variable is false (the new number is unique) then add it to the sequence
  }

  //if the mutiple choice options does not contain the answer note then replace one of the options as the answer

  if (containAnswer)
  {
    int randomIndex = random(0, sizeOfSequence); // generate a number from 0-4
    mutipleChoiceOptions[randomIndex] = answerNote;
  }

  bool userHasNotAnswer = true;
  //This code is to display the mutiple choice options
  const char *choiceOptions[] = {"A", "B", "C", "D", "E"};
  int i = 0;
  int userChoice = 0;
  while (userHasNotAnswer)
  {
    lcd.clear();
    lcd.print("Option "); // write in the lcd screen option number
    lcd.print(choiceOptions[i]);
    lcd.print("  ");
    lcd.print(mutipleChoiceOptions[i]);
    tone(buzzerPin, mutipleChoiceOptions[i]); // play the buzzer

    delay(5000); // delay for 5 second

    if (digitalRead(buttonPin) == LOW)
    {                            // when a user has press the button
      userHasNotAnswer = false;      //set the boolean to false
      tone(buzzerPin, 272, 10);  //emit a short beep when the button is pressed
      lcd.clear();               // clear screen
      lcd.print("You Selected"); // print on the screen that You selected Option X
      lcd.setCursor(0, 1);
      lcd.print("Option ");
      lcd.print(choiceOptions[i]);
      delay(10000);
      userChoice = mutipleChoiceOptions[i];
    }
    if (userHasNotAnswer)
    {
      i = i + 1;
      if (i == sizeOfSequence)
      {
        i = 0;
      }
    }
  }

  //check To see if user is right
  lcd.clear();
  lcd.print("Results");
  delay(2000);

  lcd.clear();
  lcd.print("The note play"); // print on the lcd screen the question : "Which note played at A"
  lcd.setCursor(0, 1);
  lcd.print("at Option ");
  lcd.print(options[answerNoteIndex]);
  lcd.print("= ");
  lcd.print(answerNote);
  delay(3000);

  lcd.clear();
  lcd.print("You Selected"); // print on the lcd screen the question : "Which note played at A"
  lcd.setCursor(0, 1);
  lcd.print("at Option ");
  lcd.print(choiceOptions[answerNoteIndex]);
  lcd.print("= ");
  lcd.print(userChoice);
  delay(3000);

  lcd.clear();
  if (userChoice == answerNote)
  {
    lcd.print("You were correct");
  }
  else
  {
    lcd.print("You were wrong");
  }
  delay(5000);
}
