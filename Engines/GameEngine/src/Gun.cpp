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
    timeBeforeAttack += attackDownTime;
    for (std::size_t i=0; i<attackDownTime; i++){
        sleep(1000);
        timeBeforeAttack--;
    }
    return (timeBeforeAttack==0);   
}

void Gun::stopAttack(){

}