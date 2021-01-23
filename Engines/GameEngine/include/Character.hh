#pragma Once
#include <string>
#include <iostream>
#include <vector>
#include "Gun.hh"
#include "Melee.hh"
#include "PowerUp.hh"

class Character {
  private:
    std::string _name; //= "Generic Character" by default
    int _health; //=100 by default
  public:
  //Constructors
    Character();
    Character(std::string name);
    Character(std::string name, int health); //A single constructor is required with default values
  //Methods
    int getHealth();
    void getHit(int Value);
    virtual void attack();
};