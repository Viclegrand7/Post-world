#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif

#ifndef RV_ZD_STRING
#define RV_ZD_STRING
#include <string>
#endif

#ifndef RV_ZD_CAMERA_H
#define RV_ZD_CAMERA_H
#include "Camera.hh"
#endif

#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif

#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_WEAPON_H
#define RV_ZD_WEAPON_H
#include "Weapon.hh"
#endif





class Player {
	std :: string att_name;
	CollisionSphere att_coll; 	//This has to change
	int att_health;
	Vector3f att_gravity;
	Vector3f att_dir;			//Where player directs. Includes gravity
	bool att_doesLand, att_isColliding, att_isSprinting;
	float att_sprintSpeed, att_speed, att_mouseSpeed;
	float att_stamina, att_staminaMax;
	int att_score;				//Do we?

	int att_head;

//	Weapon *att_weapons[3]; //Honestly I oculd just do that right?
	std :: vector <Weapon *> att_weapons;
	unsigned int att_curWeapon;
public:
	Camera att_cam;					//Will be easier

	Player(const char* n, const CollisionSphere &coll, Weapon *weapon);
	void update(std :: vector <CollisionPlane> &collPlane);
	void display();
	void jump();
	void sprint();
	void noSprint();

	std :: string &getName();
	int getHealth();
	CollisionSphere &getSphere();
	int getScore();

	void addHealth(int h);
	void addScore(int p);
	void setPos(const Vector3f &pos);

	void addWeapon(Weapon *weapon);
	void changeWeapon(unsigned int num);
	void nextWeapon();
	void prevWeapon();
	Weapon *getCurWeapon();

	~Player();
};