#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"

class Character {
  protected:
    std::string _name;  //= "Generic Character" by default
    int _health;  //=20 by default
  public:
  //Constructors
    Character();
    virtual ~Character();
  //Methods
    int getHealth();  //return Health of character
    bool getHit(int Value); //return true if Health ==0 ; else : false
    virtual bool toAttack()=0;
};
