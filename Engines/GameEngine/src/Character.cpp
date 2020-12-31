#include "Character.hh"

Character :: Character(){name = "Generic Character", health = 100;}
Character :: Character(std::string name){name = name, health = 100;}
Character :: Character(std::string name, int health){name = name, health = health;}

int Character::getHealth(){
    return health;
}

void Character::getHit(int Value){
    health = health - Value;
}
