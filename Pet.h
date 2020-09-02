/*
This class will contain the information for our pet
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"
class Pet
{
  public:
    Pet(const char * name,const char * image, int age, int weight);
    const char * isHungry();
    void feedMe();
  private:
    const char * _name;
    const char * _image;
    int _age;
    int _weight;
    bool _isHungry;
};

#endif