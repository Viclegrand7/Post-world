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
    Gun();
  //Methods
    int getCurMag();
    int getCurBull();
    void addBullet(int value);
    void reload();
};