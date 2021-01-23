#include "Character.hh"

Character :: Character(){name = "Generic Character", health = 100;}
Character :: Character(std::string name){name = name, health = 100;}
Character :: Character(std::string name, int health){name = name, health = health;}
//Initiate before curli braces {}, after colon :
//Ex Character(std :: string name = "Generic Character", int health = 100) : name(name), health(health) {}

//As a rule of thumb, avoid having attributes with same name as function, you might shadow them
//Ex of names : _name, att_name, aName, attNamae,...

int Character::getHealth(){
    return health;
}

void Character::getHit(int Value){
    health = health - Value;
}
