#include "Melee.hh"

Melee::Melee(std::string name, int damage, bool isAuto, int timeBeforeAttack, int attackDownTime, float range, int secondaryDownTime, int secondaryCost) : Weapon(name, damage, isAuto, timeBeforeAttack, attackDownTime){
    range = range;
    secondaryDownTime = secondaryDownTime;
    secondaryCost = secondaryCost;
}

float Melee::getRange(){
    return range;
}

bool Melee::secondary(){
    //to complete
}