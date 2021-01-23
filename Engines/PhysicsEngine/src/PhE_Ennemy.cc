#include "PhE_Ennemy.hh"

#include <cmath>

void Physic :: Ennemy :: testCollisionWall(const std :: vector<CollisionBox *> &walls) {
	Vector3f tmp(att_fakeBox.att_center);
	for (unsigned int i = 0 ; i < walls.size() ; ++i)
		sphereBox(att_fakeBox, walls[i]);
	if (tmp == att_fakeBox.att_center)
		return;
	tmp -= att_fakeBox.att_center;
	moveDir(tmp);
}

void testCollisionTeamates(const std :: vector<Ennemy *> &ennemies) {
	Vector3f tmp(att_fakeBox.att_center);
	for (unsigned int i = 0 ; i < ennemies.size() ; ++i)
		if (&ennemies[i] != this)
			sphereBox(att_fakeBox, ennemies[i]);
	if (tmp == att_fakeBox.att_center)
		return;
	tmp -= att_fakeBox.att_center;
	moveDir(other);
}

void moveDir(const Vector3f &other) {
	att_head -= other;
	att_torso -= other;
	att_legs[0] -= other;
	att_legs[1] -= other;
	att_arms[0] -= other;
	att_arms[1] -= other;
}

bool doesGetHit(const Vector3f &pos, const Vector3f &dir, float &dis, Vector3f &collisionPoint) {
	if (!raySphere(pos, dir, att_fakeBox, dis, collisionPoint))
		return false; //No collision
	bool tmp(	raySphere(pos, dir, att_head, dis, collisionPoint)); 	//Headshot;
		tmp &=	rayBox(pos, dir, att_torso, dis, collisionPoint);		//Torso shot
		tmp &=	rayBox(pos, dir, att_arms[0], dis, collisionPoint);		//Arm shot
		tmp &=	rayBox(pos, dir, att_arms[1], dis, collisionPoint);		//Arm shot
		tmp &=	rayBox(pos, dir, att_legs[0], dis, collisionPoint);		//Leg shot
		tmp &=	rayBox(pos, dir, att_legs[1], dis, collisionPoint);		//Leg shot
}

void update(const Vector3f &character, const std :: vector<Ennemy *> &ennemies, const std :: vector <CollisionBox *> &wall, float gravity) {
		Vector3f direction(character - att_fakeBox.att_center);
		direction.normalize();

		Vector3f previousPos(att_fakeBox.att_center);
		direction *= att_speed;
		direction -= gravity;
		att_fakeBox.att_center += direction;
		moveDir(-direction);
		testCollisionWall(wall);
		testCollisionTeamates(ennemies);

		att_rotation.att_y = std :: acos(direction.att_z);
		if (direction.att_x > 0) //Honestly I can't remember the reason why
			att_rotation.att_y = - att_rotation.att_y;
}
