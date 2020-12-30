#pragma once
#include <iostream>
#include <string>

class Item{
  private:
    std::string name;
  public:
  //Constructor
    Item();
  //Methods
    virtual int use();
    virtual std::string giveName();
};