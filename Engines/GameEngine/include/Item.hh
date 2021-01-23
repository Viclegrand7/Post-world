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
    int use(){
      return 1;
    };
    std::string giveName(){
      return name;
    }
};