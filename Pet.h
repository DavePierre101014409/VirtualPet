/*
This class will contain the information for our pet
*/
#ifndef PET_H
#define PET_H

#include "Arduino.h"

class Pet
{
  public:
    Pet();
    Pet(const char * name,const char * image, int age, int weight);
    bool isHungry();
    bool isHappy();
    void feedMe();
    void makeHappy();
    const char * getName();
    const char * getImage();
    int getAge();
    int getWeight();
    void setName(const char * newName);
    void setImage(const char * newImage);
    void setAge(int newAge);
    void setWeight(int newWeight);
    
    

  private:
    const char * _name;
    const char * _image;
    int _age;
    int _weight;
    bool _isHungry;
    bool _isHappy;
};

#endif
