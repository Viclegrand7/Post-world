#pragma once
#include "Character.hh"

class Player : public Character{
  protected:
    int maxHealth;
    int stamina;
    int maxStamina;
    int score;
    bool isSprinting;
    std::vector<Weapon *>  weapons; 
    Melee* knife; //
    unsigned int currentWeapon; // knife: 0

  public:
  //Constructor
    Player();
    Player(Melee *_knife, std :: vector <Weapon *> _weapons);
    ~Player();
  //Methods
    unsigned int &getCurrentWeapon(){return currentWeapon;}
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
    void reset() {currentWeapon ? weapons[currentWeapon - 1]->reset() : knife->reset();}
    bool isAutoAndShooting();
    bool isRunning() {return isSprinting;}
};