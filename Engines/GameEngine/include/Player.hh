#pragma once
#include "Character.hh"

class Player : public Character{
  private:
    int maxHealth;
    int stamina;
    int maxStamina;
    int score;
    bool isSprinting;
    std::vector<Item *>  weapons; 
    Item* knife; //
    unsigned int currentWeapon; // knife: 0

  public:
  //Constructor
    Player();
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
    Item* dropWeapon();
    int getCurMag();
    int getCurBull();
    Item* use(Item& object); 
    bool secondary();
    void reload();
    void toattack();
    int getWeaponDamage();
};