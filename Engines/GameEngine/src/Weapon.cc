#include "Weapon.hh"

Weapon::Weapon() : Item(), _damage(1), _isAuto(false), _timeBeforeAttack(0), _attackDownTime(0){}
Weapon::Weapon(bool isAuto, int damage, int attackDownTime) : Item(), _damage(damage), _isAuto(isAuto), _timeBeforeAttack(0), _attackDownTime(attackDownTime){}
int Weapon::getDamage(){
    return _damage;
}

bool Weapon::isAuto(){
    return _isAuto;
}

void Weapon::upgrade(int added_damage){
    _damage += added_damage;
}

void Weapon::countDown(){
    if (_timeBeforeAttack != 0)
        _timeBeforeAttack--;
}