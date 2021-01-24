#pragma once
#include "Weapon.hh"

class Melee : public Weapon{
  private:
    float _range;
    int _secondaryDownTime;

  public:
  //Conctructor
    Melee();
    Melee(int damage, int attackDownTime, float range, int secondaryDownTime);
  //Methods
    int use(){return -2;}
    float getRange();
    bool secondary();
    bool attack();

    void stopAttack(){};
    int getCurMag(){return 0;}
    int getCurBull(){return 0;}
    void addBullet(int value){};
    void reload(){};
};