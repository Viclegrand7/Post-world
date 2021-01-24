#pragma once
#include "Weapon.hh"
#include "Character.hh"

class Gun : public Weapon{
  private:
    int _curMagazine;
    int _maxMagazine;
    int _curBullet;
    int _maxBullet;
    bool _isAiming;
    bool _isShooting;
    bool _isReloading;
    float _precision;

  public:
  //Conctructor
    Gun();
    Gun(int damage, bool isAuto, int attackDownTime, int maxMagazine, int maxBullet, float precision);
  //Methods
    int getCurMag();
    int getCurBull();
    void addBullet(int value);
    void reload();
    bool attack();
    void stopAttack();
    bool secondary();
    float getRange(){return 0;}
};