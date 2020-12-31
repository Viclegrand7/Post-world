#pragma once
#include "Item.hh"

class PowerUp : public Item{
  private:
    int id;
  public:
  //Constructor
    PowerUp(std::string name, int id) : Item(name){id=id;}
  //Methods
};