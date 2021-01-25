#pragma once
#include "Character.hh"

class Ennemy : public Character{
  private:
    bool _isDead;
    int _damage;
    int _attackDownTime; //Time required before next attack
    int _timeBeforeAttack; //Time before Attack

  public:
  //Constructor
    Ennemy();
    Ennemy(int damage, int attackDownTime);
  //Methods
    int getDamage();
    bool isDead();
    bool toAttack(); //return True if is possible to attack
    void upgrade(); //upgrade Ennemy'a speed of attack
};