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




class Player {
	std :: string att_name;
	CollisionSphere att_coll; 	//This has to change
	int att_health;
	Vector3f att_gravity;
	Vector3f att_dir;			//Where player directs. Includes gravity
	bool att_doesLand, att_isColliding, att_isSprinting;
	float att_sprintSpeed, att_speed, att_mouseSpeed;
	float att_stamina;
	int att_score;				//Do we?
public:
	Camera att_cam;					//Will be easier

	Player(const char* n, const CollisionSphere &coll);
	void update(std :: vector <CollisionPlane> &collPlane);
	void display();

	std :: string &getName();
	int getHealth();
	CollisionSphere &getSphere();
	int getScore();

	void addHealth(int h);
	void addScore(int p);
	void setPos(const Vector3f &pos);

	~Player();
};