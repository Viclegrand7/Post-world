#pragma once
#include "Character.hh"

class Player : public Character{
  private:
    int maxHealth;
    int stamina;
    int maxStamina;
    int score;
    bool isSprinting;
    std::vector<Weapon *>  weapons;
    Melee* knife;
    unsigned int currentWeapon;

  public:
  //Constructor
    Player();
  //Methods
    int getMaxHealth();
    int getStamina();
    int getMaxStamina();
    void sprint();
    void stopSprint();
    int getScore();
    void changeWeapon(unsigned int num);
    void prevWeapon();
    void nextWeapon();
    bool dropWeapon();
    int getCurMag();
    int getCurBull();
    void use(Item& object);
    bool secondary();
    void reload();
    int getHealth();
    void getHit(int value);
    void attack();
};