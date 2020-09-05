#include <LiquidCrystal.h> //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int buzzerPin = 6;
int buttonPin = 2;

void setup()
{
  // put your setup code here, to run once:

  lcd.begin(16, 2);
}

void loop()
{
  runGame();
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
