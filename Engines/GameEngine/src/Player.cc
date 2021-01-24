#include "Player.hh"

Player::Player() : Character(){}

Player::~Player(){
    weapons.clear();
}

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
        currentWeapon = weapons.size();
    else
        currentWeapon --;           //Both weapon 0 and 2 go to Weapon 1
}

void Player::nextWeapon(){
    if (currentWeapon == weapons.size())
        currentWeapon = 0;
    else
        currentWeapon ++;
}

Weapon* Player::dropWeapon(){
    Weapon* drop;
    if (currentWeapon != 0){
        drop = weapons[currentWeapon];
        weapons.erase(weapons.begin()+currentWeapon); //Should not be able to drop the knife. Maybe it's better if it returns a Weapon* actually, so it goes on the floor. Not sure
        currentWeapon = 0;
    }
    else
        drop=NULL;
    
    return drop;
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
    return knife->secondary();
}

void Player::reload(){
    weapons[currentWeapon]->reload();
}

void Player::toattack(){
    while (1){ 
        weapons[currentWeapon]->attack();
    }
}

