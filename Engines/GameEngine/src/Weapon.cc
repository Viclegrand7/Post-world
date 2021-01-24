#include "Weapon.hh"

Weapon::Weapon() : Item(), _damage(1), _isAuto(false), _timeBeforeAttack(0), _attackDownTime(0){}
Weapon::Weapon(bool isAuto, int damage, int attackDownTime) : Item(), _damage(damage), _isAuto(isAuto), _timeBeforeAttack(0), _attackDownTime(attackDownTime){}
int Weapon::getDamage(){
    return _damage;
}

bool Weapon::isAuto(){
    return _isAuto;
}
