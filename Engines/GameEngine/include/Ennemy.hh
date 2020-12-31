#pragma once
#include "Character.hh"

class Ennemy : public Character{
  private:
    bool isDead;
    int damage;
    int attackDownTime;
    int timeBeforeAttack;

  public:
  //Constructor
    Ennemy();
  //Methods
    int getDamage();
    bool isDead();
    Item randomDrop();
    int getHealth();
    void getHit(int value);
    void attack();
};