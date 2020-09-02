/*
  Pet.cpp - Library for flashing Morse code.
*/

#include "Arduino.h"
#include "Pet.h"

 Pet(const char * name,const char * image, int age, int weight)
{
 _name = name;
 _image = image;
 _age = age;
 _weight = weight;
 _isHungry = true;
  
}

void Pet::feedMe()
{
    //add text to make chop noise
    _weight +=1;
    hungry = false;
}


void Pet::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}