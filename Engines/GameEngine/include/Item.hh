#pragma once
#include <iostream>
#include <string>
#include <unistd.h>

class Item{
  protected:
    std::string name;
  public:
  //Constructor
    Item(std::string name){name = name;}
  //Methods
    virtual int use()=0;
    virtual std::string giveName()=0;
};