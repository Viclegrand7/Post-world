#pragma once
#include "Character.hh"

class Ennemy : public Character{
  private:
    bool _isDead;
    int _damage;
    int _attackDownTime;
    int _timeBeforeAttack;

  public:
  //Constructor
    Ennemy();
    Ennemy(int damage, int attackDownTime);
  //Methods
    int getDamage();
    bool isDead();
    void toattack();
    void upgrade();
};