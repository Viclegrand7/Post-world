#include "Ennemy.hh"

Ennemy::Ennemy() : Character(), _isDead(false), _damage(0), _attackDownTime(0), _timeBeforeAttack(0){}
Ennemy::Ennemy(int damage, int attackDownTime) : Character(), _isDead(false), _damage(damage), _attackDownTime(attackDownTime), _timeBeforeAttack(0){}

int Ennemy::getDamage(){
    return _damage;
}

bool Ennemy::isDead(){
    if (this->getHealth() == 0)
        _isDead = true;
    return _isDead;
}

bool Ennemy::toAttack(){     
    if (!_isDead && _timeBeforeAttack == 0){
        _timeBeforeAttack += _attackDownTime;
        return true;
    }
    return false;
}

void Ennemy::upgrade(){
    if (_timeBeforeAttack != 0)
        _timeBeforeAttack--;
}