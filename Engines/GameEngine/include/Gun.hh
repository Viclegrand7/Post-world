#pragma once
#include "Weapon.hh"
#include "Character.hh"

class Gun : public Weapon{
  private:
    int _curMagazine; //Magazine Curve : default = 20
    int _maxMagazine; //default = 20
    int _curBullet; //default = 20
    int _maxBullet; //default = 20
    bool _isAiming; //to tell if is Aiming : default = false
    bool _isReloading; //to tell if is Reloading : default = false
    float _precision; //precision of shoot

  public:
  //Conctructor
    Gun();
    Gun(int damage, bool isAuto, int attackDownTime);
    Gun(int damage, bool isAuto, int attackDownTime, int maxMagazine, int maxBullet, float precision);
  //Methods
    int use(){return -1;}
    int getCurMag();
    int getCurBull();
    void addBullet(int value);
    void reload();
    bool attack();
    void stopAttack();
    bool secondary();
    bool &isReloading() {return _isReloading;}
    bool &isAiming() {return _isAiming;}
    float getRange(){return 0;}
};