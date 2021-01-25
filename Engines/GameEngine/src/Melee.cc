#include "Melee.hh"
Melee::Melee() : Weapon(), _range(0), _secondaryDownTime(0){} 

Melee::Melee(int damage, int attackDownTime, float range, int secondaryDownTime) : Weapon(false, damage, attackDownTime){
    _range = range;
    _secondaryDownTime = secondaryDownTime;
}

float Melee::getRange(){
    return _range;
}

bool Melee::secondary(){
    if (_timeBeforeAttack == 0){
        _timeBeforeAttack += _secondaryDownTime;
		return true;
    }
    return false;  
}

bool Melee::attack(){
    if (_isShooting && _timeBeforeAttack == 0){
        _timeBeforeAttack += _attackDownTime;
        return true;
    }
    return false;
}