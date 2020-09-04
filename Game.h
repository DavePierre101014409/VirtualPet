#include <LiquidCrystal.h> //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup()
{
  // put your setup code here, to run once:

    lcd.begin(16,2);

}

void loop()
{
    int buzzerPin = 6;

    //   note  frequency
    //   c     262 Hz
    //   d     294 Hz
    //   e     330 Hz
    //   f     349 Hz
    //   g     392 Hz
    //   a     440 Hz
    //   b     494 Hz
    //   C     523 Hz

    // took notes from the digital frequency circuit
    const int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};
    const int numberOfNotes = 8;
    const int sizeOfSequence = 5;
    randomSeed(analogRead(0));        //reset the random seed 
    int currentNoteIndex = 0;         //set the current note to intially be 0
    int noteSequence[sizeOfSequence]; // this array will contain the notes that will be played for each game
    for (int i = 0; i < sizeOfSequence; i++)
    {
      currentNoteIndex = random(0, numberOfNotes); // get a random value from 0 and 7 to be a index that represent a note
      noteSequence[i] = notes[currentNoteIndex];   //add the note in the note sequence
    }



    //This will play the song for a second a write the option on the screen
    int options[] = {1,2,3,4,5};
    for (int i = 0; i < sizeOfSequence; i++)
    {
    
        lcd.clear();
              
        lcd.print("Option ");// write in the lcd screen option number
        lcd.print(options[i]);
        lcd.print("  ");
        lcd.print(noteSequence[i]);
        tone(buzzerPin, noteSequence[i]);// play the buzzer
        delay(10000);// delay for 1 second
      
    }

    int mutipleChoiceOptions[] = {-1,-1,-1,-1,-1}; // create an array of mutiple choice options

    randomSeed(analogRead(0)); //reset the random seed (Arduino needs this to generate truly random numbers
    //generate question and print it out
    int answerNoteIndex = random(0, sizeOfSequence); // generate a number from 0-4
    lcd.clear();
    lcd.print("Which note played"); // print on the lcd screen the question : "Which note played at A"
    lcd.setCursor(0, 1);
    lcd.print("at" + options[answerNoteIndex]);
    delay(1000);

    bool hasNotAnswer = true;
    
    for (int i = 0; i < sizeOfSequence; i++)
    { //do this until all 5 postions are filled

      int currentNote = 0;      //variable to hold the current number
      boolean hasMatch = false; //does the currentNumber match any of the previous numbers?
    

      //generate random numbers until you've generated one that doesn't match any of the other numbers in the array
      do
      {
        currentNote = notes[random(0, numberOfNotes)]; //generate a random number from 0 to 7
        hasMatch = false;                                 //we haven't checked for matches yet, so start by assuming that it doesn't match
        bool hasAnswer = false;
        for (int i = 0; i < sizeOfSequence; i++)
        { //for all 5 numbers in the array
          if (currentNote == mutipleChoiceOptions[i])
          {                  //does the currentNote match any of the numbers?
            hasMatch = true; //if so, set the match variable to true
          }
          if (mutipleChoiceOptions[i] == noteSequence[answerNoteIndex])
          {
            hasAnswer = true;
          }
        }
      } while (hasMatch == true);              //if the match variable is true, generate another random number and try again
      mutipleChoiceOptions[i] = currentNote; //if the match variable is false (the new number is unique) then add it to the sequence
    }
    //if the mutiple choice options does not contain the answer note then replace one of the options as the answer
    if (hasNotAnswer)
    {
      int randomIndex = random(0, sizeOfSequence); // generate a number from 0-4
      mutipleChoiceOptions[randomIndex] = noteSequence[answerNoteIndex]; 
    }

    //This code is to display the mutiple choice options
    const char * choiceOptions[] = {"A","B","C","D","E"};
    for (int i = 0; i < sizeOfSequence; i++)
    {
    
        lcd.clear();
        lcd.print("Option ");// write in the lcd screen option number
        lcd.print(choiceOptions[i]);
        lcd.print("  ");
        lcd.print(mutipleChoiceOptions[i]);
        tone(buzzerPin, mutipleChoiceOptions[i]);// play the buzzer
        delay(10000);// delay for 1 second
      
    }
}

  ////GENERATES A RANDOM ORDER FOR NOTE
  //int * generateRandomNoteSequence(int numberOfNotes){
  //    randomSeed(analogRead(0));            //reset the random seed (Arduino needs this to generate truly random numbers
  //
  //    int currentNoteIndex = 0; //set the current note to intially be -1
  //
  //    int noteSequence[]  = {-1,-1,-1,-1,-1}; // this array will contain the notes that will be played for each game
  //    for (int i = 0; i < numberOfNotes; i++) {
  //        currentNoteIndex = random(0, numberOfNotes);  // get a random value from 0 and 8 to be a index that represent a note
  //        noteSequence[currentNoteIndex] = notes[currentNoteIndex]; //set the note to be in the note sequence
  //
  //    }
  //    return noteSequence;
  //}
