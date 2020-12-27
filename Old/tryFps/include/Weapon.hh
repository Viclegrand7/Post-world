#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_IOSTREAM
#define RV_ZD_IOSTREAM
#include <iostream>
#endif

#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif

class Weapon {
	std :: vector <unsigned int> att_frames;
	unsigned int att_look;
	unsigned int att_animation;
	unsigned int att_fire;
	unsigned int att_reload;
	Vector3f att_positionExp;
	Vector3f att_rotationExp;

	Vector3f att_position;
	Vector3f att_rotation;

	Vector3f att_positionAim;
	Vector3f att_rotationAim;

	Vector3f att_curPos;
	Vector3f att_curRot;

	float att_precision;
	float att_aimPrecision;
	int att_damage;
	bool att_isAim;
	bool att_isReloading;
	bool att_isAuto;
	bool att_isFiring;
	bool att_isTest;

	unsigned int att_magazine;
	unsigned int att_magazineMax;
	unsigned int att_curBullets;
	unsigned int att_maxBullets;

	unsigned int att_lastShot; //How many frames ago
	unsigned int att_speed;

	unsigned int att_curFrame;
	unsigned int att_curMode; //1 normal, 2 fire, 3 reload

	std :: string att_name;
public:
	Weapon(std :: vector <unsigned int> &animation, unsigned int look, unsigned int normal, unsigned int fire, unsigned int reload, bool isAuto, Vector3f pos, 
		Vector3f rot, Vector3f aimPos, Vector3f aimRot, float prec, float aimPrec, unsigned int dmg, unsigned int maxB, unsigned int allB, unsigned int speed, const std :: string &name);
	~Weapon();
	void update();
	void show();

	bool fire(Vector3f &dir, const Vector3f &camDir);
	void stopFire();
	void reload();
	void aim();

	void test();

	void addB(unsigned int num);
	void setB(unsigned int num);

	int getDmg();
	unsigned int getAmmo();
	unsigned int getAllAmmo();
	std :: string getName();
	std :: vector <unsigned int> &getAnimation();
	bool isAim();
	unsigned int getLook();
};
