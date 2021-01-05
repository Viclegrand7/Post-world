#include "Weapon.hh"

Weapon::Weapon(std::string name, int damage, bool isAuto, int timeBeforeAttack, int attackDownTime) : Item(name){
    damage = damage;
    isAuto = isAuto;
    timeBeforeAttack = timeBeforeAttack;
    attackDownTime = attackDownTime;
}

int Weapon::getDamage(){
    return damage;
}

bool Weapon::isAuto(){
    return isAuto;
}



void Weapon::stopAttack(){
    
}