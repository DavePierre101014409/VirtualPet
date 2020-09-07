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
    Pet(String name,String image, int age, int weight);
    bool isHungry();
    bool isHappy();
    void feedMe();
    void makeHappy();
    String getName();
    String getImage();
    int getAge();
    int getWeight();
    void setName(String newName);
    void setImage(String newImage);
    void setAge(int newAge);
    void setWeight(int newWeight);
    
    

  private:
    String  _name;
    String _image;
    int _age;
    int _weight;
    bool _isHungry;
    bool _isHappy;
};

#endif
