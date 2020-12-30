#pragma once
#include "Item.hh"

class Weapon : public Item{
  private:
    int damage;
    bool isAuto;
    int timeBeforeAttack;
    int attackDownTime;
  public:
  //Constructor
    Weapon();
  //Methods
    int getDamage();
    bool isAuto();
    bool attack();
    void stopAttack();
    virtual int getCurMag();
    virtual int getCurBull();
    virtual void addBullet(int value);
    virtual void reload();
    virtual float getRange();
    virtual bool secondary();

};