#pragma once
#include <iostream>
#include <string>
#include <unistd.h>

class Item{
  protected:
    std::string _name;
  public:
  //Constructor
    Item(): _name("Generic item"){}
    virtual ~Item(){}
  //Methods
    virtual int getDamage()=0;
    virtual bool isAuto()=0;
    virtual void upgrade(int added_damage)=0;
    virtual int use()=0;
    virtual bool attack()=0;
    virtual void stopAttack()=0;
    virtual int getCurMag()=0;
    virtual int getCurBull()=0;
    virtual void addBullet(int value)=0;
    virtual void reload()=0;
    virtual float getRange()=0;
    virtual bool secondary()=0;
    std::string giveName(){
      return _name;
    }
};