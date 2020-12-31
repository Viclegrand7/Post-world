#pragma once
#include "Weapon.hh"

class Gun : public Weapon{
  private:
    int curMagazine;
    int maxMagazine;
    int curBullet;
    int maxBullet;
    bool isAiming;
    bool isShooting;
    bool isReloading;
    float precision;

  public:
  //Conctructor
    Gun(std::string name, int damage, bool isAuto, int timeBeforeAttack, int attackDownTime, int maxMagazine, int maxBullet, float precision;
  //Methods
    int getCurMag();
    int getCurBull();
    void addBullet(int value);
    void reload();
};