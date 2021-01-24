#include "Character.hh"

Character :: Character() : _name("Generic character"), _health(20){}

Character :: ~Character() {}

int Character::getHealth(){
    return _health;
}

void Character::getHit(int Value){
    _health = _health - Value;
}
