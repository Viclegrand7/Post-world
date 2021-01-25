#include "Character.hh"

Character :: Character() : _name("Generic character"), _health(20){}

Character :: ~Character() {}

int Character::getHealth(){
    return _health;
}

bool Character::getHit(int Value){
    _health = _health - Value;
    if (_health <= 0)
    	return true;
    return false;
}
