#pragma once
#include "Item.hh"

class Weapon : public Item{
  protected:
    int _damage;
    bool _isAuto;
    int _timeBeforeAttack;
    int _attackDownTime;
  public:
  //Constructor
    Weapon();
    Weapon(bool isAuto, int damage, int attackDownTime);
    virtual ~Weapon(){}
  //Methods
    int getDamage();
    bool isAuto();
    virtual bool attack()=0;
    virtual void stopAttack()=0;
    virtual int getCurMag()=0;
    virtual int getCurBull()=0;
    virtual void addBullet(int value)=0;
    virtual void reload()=0;
    virtual float getRange()=0;
    virtual bool secondary()=0;

};