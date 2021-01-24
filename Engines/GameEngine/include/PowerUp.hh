#pragma once
#include "Item.hh"

class PowerUp : public Item{
  private:
    int _id; //Each id match to one functionnality
  public:
  //Constructor
    PowerUp(int id) : Item(), _id(id){}
    PowerUp(std::string name, int id) : Item(){_id=id; _name = "Power Up Potion";}
  //Methods
    int use(){return _id;}
    int getDamage(){return 0;}
    bool isAuto(){return false;}
    void upgrade(int added_damage){}
    bool attack(){return false;}
    void stopAttack(){}
    int getCurMag(){return 0;}
    int getCurBull(){return 0;}
    void addBullet(int value){}
    void reload(){}
    float getRange(){return 0;}
    bool secondary(){return false;}
};