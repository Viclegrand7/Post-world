#pragma once
#include "Weapon.hh"

class Melee : public Weapon{
  private:
    float range;
    int secondaryDownTime;
    int secondaryCost;

  public:
  //Conctructor
    Melee(std::string name, int damage, bool isAuto, int timeBeforeAttack, int attackDownTime, float range, int secondaryDownTime, int secondaryCost);
  //Methods
    float getRange();
    bool secondary();
};