#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif

#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif

#ifndef RV_ZD_GLU_H
#define RV_ZD_GLU_H
#include <GL/glu.h>
#endif




class Ennemy {
	std :: vector <unsigned int> att_frames;
	unsigned int att_walk, att_attack, att_death;
	unsigned int att_curFrame;

	int att_health, att_damage;
	float att_speed;
	Vector3f att_direction, att_rotation;
	bool att_isMoving, att_isAttacking, att_isDead; //att_curMode?

	CollisionSphere att_collSphere;

public:
	Ennemy(const std :: vector <unsigned int> &anim, unsigned int walk, unsigned int attack, unsigned int death, int health, int damage, float speed, const CollisionSphere &cs);
	bool update(std :: vector <CollisionPlane> &cp, const Vector3f &playerLoc);
	void display();
	bool setAttack(CollisionSphere &player); 

	CollisionSphere &getCollSphere();
	void setLocation(const Vector3f &loc);
	void getHit(int dmg);
	int getHealth();
	int getDamage();
	bool isDead();

	~Ennemy() {}
};