#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"

class Character {
  protected:
    std::string _name; //= "Generic Character" by default
    int _health; //=100 by default
  public:
  //Constructors
    Character();
    virtual ~Character();
  //Methods
    int getHealth();
    void getHit(int Value);
    virtual void toattack()=0;
};
