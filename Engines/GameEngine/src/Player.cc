#include "Player.hh"

Player::Player() : Character(), maxHealth(20), stamina(5), maxStamina(5), score(0), isSprinting(false), knife(NULL), currentWeapon(-1){}

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
    if (num < weapons.size())
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
        drop = weapons[currentWeapon-1];
        weapons.erase(weapons.begin()+(currentWeapon-1)); //Should not be able to drop the knife. Maybe it's better if it returns a Weapon* actually, so it goes on the floor. Not sure
        currentWeapon = 0;
    }
    else
        drop=NULL;
    
    return drop;
}

int Player::getCurMag(){
    if (currentWeapon != 0)
        return weapons[currentWeapon-1]->getCurMag();
    return 0;
}

int Player::getCurBull(){
    if (currentWeapon != 0)
        return weapons[currentWeapon-1]->getCurBull();
    return 0;
}

Weapon* Player::use(Item& object){
    Weapon* drop = NULL;
    int type = object.use();
    if (type >= 0){
        switch (type)
        {
        case 0:
            maxStamina += 10;
            break;
        case 1:
            weapons[currentWeapon-1]->upgrade(5);
            break;
        default:
            break;
        }
    }
    else{
        if (type == -2 && knife == NULL){
            knife = (Melee* )&object;
            currentWeapon = 0;
        }
        else{
            if (weapons.size()<2){
                weapons.push_back((Weapon*)&object);
                currentWeapon = weapons.size();
            }
            else
            {
                drop = weapons[currentWeapon-1];
                weapons[currentWeapon-1] = (Weapon*)&object;
            }
        }
    }
    return drop;
}

bool Player::secondary(){
    return knife->secondary();
}

void Player::reload(){
    weapons[currentWeapon]->reload();
}

void Player::toAttack(){
    while (1){ 
        weapons[currentWeapon]->attack();
    }
}

int Player::getWeaponDamage(){
    int dam;
    if (currentWeapon == 0)
        dam = knife->getDamage();
    else
        dam = weapons[currentWeapon -1]->getDamage();
    return dam;
}