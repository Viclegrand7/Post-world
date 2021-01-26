#pragma once
#include "Item.hh"

class Weapon : public Item{
  protected:
    int _damage; //Weapon's damage : default = 0
    bool _isAuto; //if isAuto = True : attack automatically when it's possible, default = false
    int _timeBeforeAttack; //if =0 : is possible to attack , default = 0
    int _attackDownTime;  //time required before nect attack : default = 0
    bool _isShooting; //to tell if weapon is attacking : default = false
  public:
  //Constructor
    Weapon(); 
    Weapon(bool isAuto, int damage, int attackDownTime);
    virtual ~Weapon(){}
  //Methods
    int getDamage();
    bool isAuto();
    void upgrade(int added_damage); //upgrade weapon's damage
    bool countDown();  //timeBeforeAttack-- until = 0
    bool &isShooting(){return _isShooting;}
    virtual void reset() {_isShooting = false;}
    virtual int use()=0;
    virtual bool attack()=0;
    virtual void stopAttack()=0;
    virtual int getCurMag()=0;
    virtual int getCurBull()=0;
    virtual void addBullet(int value)=0;
    virtual void reload()=0;
    virtual float getRange()=0;
    virtual bool secondary()=0;

};