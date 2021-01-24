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
};