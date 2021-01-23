#include "Player.hh"

Player::Player(std::string name) : Character(name){}

int Player::getMaxHealth(){
    return maxHealth;
}

int Player::getStamina(){
    return stamina;
}

int Player::getMaxStamina(){
    return maxStamina;
}

void Player::sprint(){
    isSprinting = true;
}

void Player::stopSprint(){
    isSprinting = false;
}

int Player::getScore(){
    return score;
}

void Player::changeWeapon(unsigned int num){
    currentWeapon = num;
}

void Player::prevWeapon(){
    if (currentWeapon == 0)
        currentWeapon = 1;
    else if (currentWeapon == 1)
        currentWeapon = weapons.size();
    else
        currentWeapon --;           //Both weapon 0 and 2 go to Weapon 1
    changeWeapon(currentWeapon);    //You already did it
}

void Player::nextWeapon(){
    if (currentWeapon == 0)
        currentWeapon = weapons.size();
    else if (currentWeapon == weapons.size())
        currentWeapon = 1;
    else
        currentWeapon ++;
    changeWeapon(currentWeapon);
}

bool Player::dropWeapon(){
    weapons.erase(weapons.begin()+currentWeapon-1); //Should not be able to drop the knife. Maybe it's better if it returns a Weapon* actually, so it goes on the floor. Not sure
    currentWeapon = 0;
    //Missing a return
}

int Player::getCurMag(){
    if (currentWeapon != 0)
        return weapons[currentWeapon]->getCurMag();
    return 0;
}

int Player::getCurBull(){
    if (currentWeapon != 0)
        return weapons[currentWeapon]->getCurBull();
    return 0;
}

void Player::use(Item& object){
    object.use();
}

bool Player::secondary(){
    return weapons[currentWeapon]->secondary();
}

void Player::reload(){
    weapons[currentWeapon]->reload();
}

void Player::attack(){
    while (weapons[currentWeapon]->isAuto()){ //Error, while(1)
        weapons[currentWeapon]->attack();
    }
}

