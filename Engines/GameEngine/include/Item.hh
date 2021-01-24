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
    virtual int use()=0;
    std::string giveName(){
      return _name;
    }
};