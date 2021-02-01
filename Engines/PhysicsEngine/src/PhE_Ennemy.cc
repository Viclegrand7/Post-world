#include "PhE_Ennemy.hh"

#include <cmath>

void Physic :: Ennemy :: testCollisionWall(const std :: vector<CollisionQuad *> &walls) {
	Vector3f tmp(att_fakeBox.att_center);
	for (unsigned int i = 0 ; i < walls.size() ; ++i)
		Physic :: Collision :: sphereQuad(att_fakeBox, *walls[i]);
	if (tmp == att_fakeBox.att_center)
		return;
	tmp -= att_fakeBox.att_center;
	moveDir(tmp);
}

void Physic :: Ennemy :: testCollisionTeamates(const std :: vector<Ennemy *> &ennemies) {
	Vector3f tmpVector(att_fakeBox.att_center);
	for (unsigned int i = 0 ; i < ennemies.size() ; ++i)
		if (ennemies[i] != this)
			Physic :: Collision :: sphereSphere(att_fakeBox, ennemies[i]->giveSphere());
	if (tmpVector == att_fakeBox.att_center)
		return;
	tmpVector -= att_fakeBox.att_center;
	moveDir(tmpVector);
}
/*
void Physic :: Ennemy :: testCollisionWall(const std :: vector<CollisionQuad *> &walls, unsigned int curFrame) {
	Vector3f tmp(att_fakeBox[curFrame].att_center);
	for (unsigned int i = 0 ; i < walls.size() ; ++i)
		Physic :: Collision :: sphereQuad(att_fakeBox[curFrame], *walls[i]);
	if (tmp == att_fakeBox[curFrame].att_center)
		return;
	tmp -= att_fakeBox[curFrame].att_center;
	moveDir(tmp);
}

void Physic :: Ennemy :: testCollisionTeamates(const std :: vector<Ennemy *> &ennemies, unsigned int curFrame) {
	Vector3f tmpVector(att_fakeBox[curFrame].att_center);
	for (unsigned int i = 0 ; i < ennemies.size() ; ++i)
		if (ennemies[i] != this)
			Physic :: Collision :: sphereSphere(att_fakeBox[curFrame], ennemies[i]->giveSphere());
	if (tmpVector == att_fakeBox[curFrame].att_center)
		return;
	tmpVector -= att_fakeBox[curFrame].att_center;
	moveDir(tmpVector);
}

void Physic :: Ennemy :: moveDir(const Vector3f &other) {
	for (unsigned int i = 0 ; i < att_head.size() ; ++i) {
		att_head[i]  -= other;
		att_torso[i] -= other;
		att_legs1[i] -= other;
		att_legs2[i] -= other;
		att_arms1[i] -= other;
		att_arms2[i] -= other;
	}
}
*/
void Physic :: Ennemy :: moveDir(const Vector3f &other) {
	att_fakeBox.att_center -= other;
	att_head  -= other;
	att_torso -= other;
	att_legs1 -= other;
	att_legs2 -= other;
	att_arms1 -= other;
	att_arms2 -= other;
}


bool Physic :: Ennemy :: doesGetHit(const Vector3f &pos, const Vector3f &dir, float *dis, Vector3f *collisionPoint) {
	if (!Physic :: Collision :: raySphere(pos, dir, att_fakeBox, dis, collisionPoint))
		return false; //No collision

	bool tmp(	Physic :: Collision :: raySphere(pos, dir, att_head, dis, collisionPoint)); 	//Headshot;
	tmp |=	Physic :: Collision :: rayBox(pos, dir, att_torso, dis, collisionPoint);		//Torso shot
	tmp |=	Physic :: Collision :: rayBox(pos, dir, att_arms1, dis, collisionPoint);		//Arm shot
	tmp |=	Physic :: Collision :: rayBox(pos, dir, att_arms2, dis, collisionPoint);		//Arm shot
	tmp |=	Physic :: Collision :: rayBox(pos, dir, att_legs1, dis, collisionPoint);		//Leg shot
	tmp |=	Physic :: Collision :: rayBox(pos, dir, att_legs2, dis, collisionPoint);		//Leg shot
	return tmp;
}
/*
bool Physic :: Ennemy :: doesGetHit(const Vector3f &pos, const Vector3f &dir, float *dis, Vector3f *collisionPoint, unsigned int curFrame) {
	if (!Physic :: Collision :: raySphere(pos, dir, att_fakeBox[curFrame], dis, collisionPoint))
		return false; //No collision
	bool tmp(	Physic :: Collision :: raySphere(pos, dir, att_head[curFrame], dis, collisionPoint)); 	//Headshot;
		tmp &=	Physic :: Collision :: rayBox(pos, dir, att_torso[curFrame], dis, collisionPoint);		//Torso shot
		tmp &=	Physic :: Collision :: rayBox(pos, dir, att_arms1[curFrame], dis, collisionPoint);		//Arm shot
		tmp &=	Physic :: Collision :: rayBox(pos, dir, att_arms2[curFrame], dis, collisionPoint);		//Arm shot
		tmp &=	Physic :: Collision :: rayBox(pos, dir, att_legs1[curFrame], dis, collisionPoint);		//Leg shot
		tmp &=	Physic :: Collision :: rayBox(pos, dir, att_legs2[curFrame], dis, collisionPoint);		//Leg shot
	return tmp;
}

void Physic :: Ennemy :: update(const Vector3f &character, const std :: vector<Ennemy *> &ennemies, const std :: vector <CollisionQuad *> &wall, float gravity, unsigned int curFrame) {
		Vector3f direction(character - att_fakeBox[curFrame].att_center);
		direction.normalize();

//		Vector3f previousPos(att_fakeBox[curFrame].att_center);
		direction *= att_speed;
		direction -= gravity;
		for (unsigned int i = 0 ; i < att_fakeBox.size() ; ++i)
			att_fakeBox[curFrame].att_center += direction;
		moveDir(-direction);
		testCollisionWall(wall, curFrame);
		testCollisionTeamates(ennemies, curFrame);

		att_rotation.att_y = std :: acos(direction.att_z);
		if (direction.att_x > 0) //Honestly I can't remember the logic behind it
			att_rotation.att_y = - att_rotation.att_y;
}
*/
void Physic :: Ennemy :: update(const Vector3f &character, const std :: vector<Ennemy *> &ennemies, const std :: vector <CollisionQuad *> &wall, float gravity) {
		Vector3f direction(character - att_fakeBox.att_center);
		direction.normalize();
		direction *= att_speed;
		direction -= gravity;
		moveDir(-direction);
		testCollisionWall(wall);
		testCollisionTeamates(ennemies);

		att_rotation.att_y = std :: acos(direction.att_z);
		if (direction.att_x > 0) //Honestly I can't remember the logic behind it
			att_rotation.att_y = - att_rotation.att_y;
}
/*
Physic :: Ennemy & Physic :: Ennemy :: operator+=(const Ennemy &other) {
	att_head.push_back(other.att_head[0]);
	att_torso.push_back(other.att_torso[0]);
	att_legs1.push_back(other.att_legs1[0]);
	att_legs2.push_back(other.att_legs2[0]);
	att_arms1.push_back(other.att_arms1[0]);
	att_arms2.push_back(other.att_arms2[0]);
	att_fakeBox.push_back(other.att_fakeBox[0]);
	return *this;
}
*/
Physic :: Ennemy & Physic :: Ennemy :: operator=(const Ennemy &other) {
	att_head = other.att_head;
	att_torso = other.att_torso;
	att_legs1 = other.att_legs1;
	att_legs2 = other.att_legs2;
	att_arms1 = other.att_arms1;
	att_arms2 = other.att_arms2;
	att_fakeBox = other.att_fakeBox;

	return *this;
}

void Physic :: Ennemy :: equals(const Physic :: CollisionSphere &sphere, bool isHead) {
	if (isHead)
		att_head = sphere;
	else {
		att_initialStupidOffsetBecause3D.att_x = 0.f;
		att_initialStupidOffsetBecause3D.att_y = sphere.att_center.att_y;
		att_initialStupidOffsetBecause3D.att_z = 0.f;
		att_fakeBox = sphere;
	}
}

void  Physic :: Ennemy :: equals(const Physic :: CollisionBox &box, char isWhat) {
	switch (isWhat) {
		case 2:
			att_torso = box;
		break;
		case 3:
			att_legs1 = box;
		break;
		case 4:
			att_legs2 = box;
		break;
		case 5:
			att_arms1 = box;
		break;
		case 6:
			att_arms2 = box;
		break;
	}
}
/*
void Physic :: Ennemy :: equals(const Physic :: CollisionSphere &sphere, bool isHead) {
	if (isHead){
		att_head.clear();
		att_head.push_back(sphere);
	}
	else{
		att_fakeBox.clear();
		att_fakeBox.push_back(sphere);
	}
}

void  Physic :: Ennemy :: equals(const Physic :: CollisionBox &box, char isWhat) {
	switch (isWhat) {
		case 2:
			att_torso.clear();
			att_torso.push_back(box);
		break;
		case 3:
			att_legs1.clear();
			att_legs1.push_back(box);
		break;
		case 4:
			att_legs2.clear();
			att_legs2.push_back(box);
		break;
		case 5:
			att_arms1.clear();
			att_arms1.push_back(box);
		break;
		case 6:
			att_arms2.clear();
			att_arms2.push_back(box);
		break;
	}
}
*/