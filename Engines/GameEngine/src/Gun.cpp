#include "Gun.hh"

Gun::Gun(std::string name, int damage, bool isAuto, int timeBeforeAttack, int attackDownTime, int maxMagazine, int maxBullet, float precision) : Weapon(name, damage, isAuto, timeBeforeAttack, attackDownTime){
    curMagazine = maxMagazine;
    maxMagazine = maxMagazine;
    curBullet = maxBullet;
    maxBullet = maxBullet;
    isAiming = false;
    isShooting = false;
    isReloading = false;
    precision = precision;
}

int Gun::getCurMag(){
    return curMagazine;
}

int Gun::getCurBull(){
    return curBullet;
}

void Gun::addBullet(int value){
    curBullet += value;
    if (curBullet > maxBullet)
        curBullet = maxBullet;
}

void Gun::reload(){             //This function should reload the weapon, aka change the magazine
    curMagazine = maxMagazine;  
    maxMagazine = maxMagazine;  //Why?
    curBullet = maxBullet;
    maxBullet = maxBullet;      //Why?
    isAiming = false;
    isShooting = false;
    isReloading = false;        //Should be true I think
    precision = precision;
}

bool Gun::attack(){
    isShooting = true;  
    timeBeforeAttack += attackDownTime;
    for (std::size_t i=0; i<attackDownTime; i++){   //Same as Weapon, something is off here
        sleep(1000);
        timeBeforeAttack--;
    }
    return isShooting;
}

void Gun::stopAttack(){
    isShooting = false;
}

bool Gun::secondary(){
    isAiming = !isAiming;
    return isAiming;
}