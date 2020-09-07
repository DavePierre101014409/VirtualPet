/*
  Pet.cpp - Library for flashing Morse code.
*/

#include "Pet.h"

Pet::Pet()
{
  // Creates a random pet details

  const int numberOfOptions = 10;                                                                                                                 // the length of options for name, image
  String nameBank[] = {"Dave", "Selena", "Lebron", "Chris", "Karyse", "Lex", "Amelie", "Julie", "Alice", "Ray"};                             // created random names to pick out of
  String imageBank[] = {"00_00", "--------0_0", ";-;", "0_0~~~~~~~~~~~", "$$$$$0-0$$$$$", "^_^", "*_*", "(_)eeeeeeeeeee", "<-#_#->", "p-q"}; // create random chracters tht will serve as the pet image

  randomSeed(analogRead(0));
  _name = nameBank[random(0, numberOfOptions)];   // pick a number that corrpeonds the name  out of the name bank
  _image = imageBank[random(0, numberOfOptions)]; // pick a number that corresponds to an image in the image bank
  _age = random(0, numberOfOptions);              //pick a number between 0 and 9
  _weight = random(1, numberOfOptions);           // pick a number between 1- 9

  _isHungry = true;
  _isHappy = false;
}

Pet::Pet(String name, String image, int age, int weight)
{
  _name = name;
  _image = image;
  _age = age;
  _weight = weight;
  _isHungry = true;
  _isHappy = false;
}

void Pet::feedMe()
{
  //add text to make chop noise
  _weight += 1;
  _isHungry = false;
}

String Pet::getName()
{
  return _name;
}

String Pet::getImage()
{
  return _image;
}

int Pet::getAge()
{
  return _age;
}

int Pet::getWeight()
{
  return _weight;
}

bool Pet::isHungry()
{
  return _isHungry;
}

void Pet::setName(String newName)
{
  _name = newName;
}

void Pet::setImage(String newImage)
{
  _image = newImage;
}

void Pet::setAge(int newAge)
{
  _age = newAge;
}

void Pet::setWeight(int newWeight)
{
  _weight = newWeight;
}

bool Pet::isHappy()
{
  return _isHappy;
}
void Pet::makeHappy()
{
  _isHappy = true;
}
