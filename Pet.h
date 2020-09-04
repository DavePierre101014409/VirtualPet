/*
This class will contain the information for our pet
*/
#ifndef PET_H
#define PET_H

#include "Arduino.h"

class Pet
{
  public:
    Pet(const char * name,const char * image, int age, int weight);
    bool isHungry();
    void feedMe();
    const char * getName();
    const char * getImage();
    int getAge();
    int getWeight();

  private:
    const char * _name;
    const char * _image;
    int _age;
    int _weight;
    bool _isHungry;
};

#endif
