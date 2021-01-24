#pragma once
#include "Item.hh"

class PowerUp : public Item{
  private:
    static int cpt;
    int _id;
  public:
  //Constructor
    PowerUp() : Item(), _id(cpt){cpt++;}
    PowerUp(std::string name, int id) : Item(){_id=id; _name = "Power Up Potion";}
  //Methods
    int use(){return 2;}
};

int PowerUp::cpt=0;