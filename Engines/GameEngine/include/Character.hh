#pragma Once
#include <string>
#include <iostream>
#include <vector>
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"

class Character {
  private:
    std::string name; //= "Generic Character" by default
    int health; //=100 by default
  public:
  //Constructors
    Character();
    Character(std::string name);
    Character(std::string name, int health);
  //Methods
    int getHealth();
    void getHit(int Value);
    virtual void attack();
};