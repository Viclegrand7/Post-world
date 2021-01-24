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
    virtual int use()=0;  //0:Melee  1:Gun   2:PowerUp
    std::string giveName(){
      return _name;
    }
};