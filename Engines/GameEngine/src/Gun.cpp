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

void Gun::reload(){
    curMagazine = maxMagazine;
    maxMagazine = maxMagazine;
    curBullet = maxBullet;
    maxBullet = maxBullet;
    isAiming = false;
    isShooting = false;
    isReloading = false;
    precision = precision;
}

bool Gun::attack(){
    isShooting = true;  
}

void Gun::stopAttack(){
    isShooting = false;
}

bool Gun::secondary(){
    isAiming = !isAiming;
}