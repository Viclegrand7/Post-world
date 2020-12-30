#pragma once
#include "Weapon.hh"

class Melee : public Weapon{
  private:
    float range;
    int secondaryDownTime;
    int secondaryCost;

  public:
  //Conctructor
    Melee();
  //Methods
    float getRange();
    bool secondary();
};