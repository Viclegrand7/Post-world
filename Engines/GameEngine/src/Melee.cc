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
    bool attack = false;
    if (_timeBeforeAttack == 0){
        attack = true;
        _timeBeforeAttack += _secondaryDownTime;
    }
    return attack;  
}

bool Melee::attack(){
    bool attack = false;
    if (_timeBeforeAttack == 0){
        _isShooting = true;
        attack = true;
        _timeBeforeAttack += _attackDownTime;
    }
    return attack;
}