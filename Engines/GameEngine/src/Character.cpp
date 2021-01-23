#include "Character.hh"

Character :: Character(std::string name = "Generic Character", int health = 100) : _name(name), _health(health){}
Character :: Character(std::string name, int health = 100) : _name(name), _health(health){}
Character :: Character(std::string name, int health): _name(name), _health(health){}
//Initiate before curli braces {}, after colon :
//Ex Character(std :: string name = "Generic Character", int health = 100) : name(name), health(health) {}

//As a rule of thumb, avoid having attributes with same name as function, you might shadow them
//Ex of names : _name, att_name, aName, attNamae,...

int Character::getHealth(){
    return _health;
}

void Character::getHit(int Value){
    _health = _health - Value;
}
