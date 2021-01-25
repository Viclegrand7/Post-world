#pragma once
#include "Weapon.hh"

class Melee : public Weapon{
  private:
    float _range; 
    int _secondaryDownTime; //Time nrequired for next attack after a secondary attack

  public:
  //Conctructor
    Melee();
    Melee(int damage, int attackDownTime, float range, int secondaryDownTime);
  //Methods
    int use(){return -2;}
    float getRange();
    bool secondary(); //secondary attack, same as attack()
    bool attack(); //to tell if it's possible to attack

  //Methods to avoid class being virtual
    void stopAttack(){};
    int getCurMag(){return 0;}
    int getCurBull(){return 0;}
    void addBullet(int value){};
    void reload(){};
};