#include "Gun.hh"

Gun::Gun() : Weapon(), _curMagazine(20), _maxMagazine(20), _curBullet(20), _maxBullet(20), _isAiming(false), _isReloading(false), _precision(0){} 

Gun::Gun(int damage, bool isAuto, int attackDownTime) : Weapon(isAuto, damage, attackDownTime), _curMagazine(20), _maxMagazine(20), _curBullet(20), _maxBullet(20), _isAiming(false), _isReloading(false), _precision(0){} 

Gun::Gun(int damage, bool isAuto,int attackDownTime, int maxMagazine, int maxBullet, float precision) : Weapon(isAuto, damage, attackDownTime){
    _curMagazine = maxMagazine;
    _maxMagazine = maxMagazine;
    _curBullet = maxBullet;
    _maxBullet = maxBullet;
    _isAiming = false;
    _isReloading = false;
    _precision = precision;
}

int Gun::getCurMag(){
    return _curMagazine;
}

int Gun::getCurBull(){
    return _curBullet;
}

void Gun::addBullet(int value){
    _curBullet += value;
    if (_curBullet > _maxBullet)
        _curBullet = _maxBullet;
}

void Gun::reload(){             //This function should reload the weapon, aka change the magazine
    if (_isShooting || _isReloading)
        return;
    if (_curMagazine == _maxMagazine || !_curBullet) {
        _isReloading = false;
        return;
    }
    if (_curBullet + _curMagazine >=_maxMagazine) {
        _curBullet -= (_maxMagazine - _curMagazine);
        _curMagazine = _maxMagazine;
        _isReloading = true;
        return;
    }
    _curMagazine += _curBullet;
    _isReloading = true;
}

bool Gun::attack(){
    if (_isShooting && _curBullet != 0 && _timeBeforeAttack == 0 && !_isReloading){
        _timeBeforeAttack += _attackDownTime;
        _curBullet--;
        _curMagazine--;
        return true;
    }
	return false;
}

void Gun::stopAttack(){
    _isShooting = false;
}

bool Gun::secondary(){
    _isAiming = !_isAiming;
    return _isAiming;
}
