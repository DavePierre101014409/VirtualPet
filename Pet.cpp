/*
  Pet.cpp - Library for flashing Morse code.
*/

#include "Pet.h"

Pet::Pet(const char * name,const char * image, int age, int weight)
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
    _isHungry = false;
}

const char * Pet::getName()
{
  return _name;
}

const char * Pet::getImage()
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
