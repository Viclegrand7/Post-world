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
    virtual int use()=0;  //-1:Weapon  >0: PowerUp1:Gun
    std::string giveName(){
      return _name;
    }
};