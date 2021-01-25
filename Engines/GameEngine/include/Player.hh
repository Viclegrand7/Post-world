#pragma once
#include "Character.hh"

class Player : public Character{
  protected:
    int maxHealth;
    int stamina;
    int maxStamina;
    int score;
    bool isSprinting;
    std::vector<Weapon *>  weapons; //Size <= 2
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
    void prevWeapon();
    void nextWeapon();
    Weapon* dropWeapon();
    int getCurMag();
    int getCurBull();
    Weapon* use(Item& object); 
    bool secondary();
    void reload();
    void update();
    bool attack();
    bool toAttack();
    int getWeaponDamage();
    bool isRunning() {return isSprinting;}
};