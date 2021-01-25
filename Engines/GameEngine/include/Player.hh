#pragma once
#include "Character.hh"

class Player : public Character{
  protected:
    int maxHealth;
    int stamina;
    int maxStamina;
    int score;
    bool isSprinting;
    std::vector<Weapon *>  weapons; //list of weapons : Size <= 2 (can contain Melee or Gun)
    Melee* knife; 
    unsigned int currentWeapon; // knife: 0 ; 1st weapon in weapons : 1

  public:
  //Constructor
    Player(); //
    ~Player();
  //Methods
    int getCurrentWeapon(){return currentWeapon;}
    int getMaxHealth();
    int getStamina();
    int getMaxStamina();
    void sprint();
    void stopSprint();
    void addScore(int value){score += value;}
    int getScore();
    void changeWeapon(unsigned int num); //num between 0 to 2
    void prevWeapon(); //change current weapon to previous Weapon in weapons
    void nextWeapon(); //change current weapon to next Weapon in weapons
    Weapon* dropWeapon(); //drop the current weapon in the hand
    int getCurMag(); //get current weapon's magic curve (if it's not knife)
    int getCurBull(); //get current weapon's Bullet curve (if it's not knife)
    Weapon* use(Item& object); //use a Item : PowerUp, Gun or Melee
    bool secondary(); //use knife's secondary
    void reload(); //reload current weapon
    void update(); //update current weapon's status : Weapon's timeBeforeAttack --
    bool attack(); //tell if current weapon could attack or not
    bool toAttack(); //change CurrentWeapon's status to isShooting, return false
    int getWeaponDamage(); //get current weapon's damage
    bool isRunning() {return isSprinting;}
};