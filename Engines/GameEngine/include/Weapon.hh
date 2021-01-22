#pragma once
#include "Item.hh"

class Weapon : public Item{
  protected:
    int damage;
    bool _isAuto;
    int timeBeforeAttack;
    int attackDownTime;
  public:
  //Constructor
    Weapon(std::string name, int damage, bool isAuto, int timeBeforeAttack, int attackDownTime);
  //Methods
    int getDamage();
    bool isAuto();
    virtual bool attack();
    virtual void stopAttack();
    virtual int getCurMag();
    virtual int getCurBull();
    virtual void addBullet(int value);
    virtual void reload();
    virtual float getRange();
    virtual bool secondary();

};