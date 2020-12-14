#ifndef RV_ZD_PLAYER_H
#define RV_ZD_PLAYER_H
#include "Player.hh"
#endif


Player :: Player(const char* n, const CollisionSphere &coll) 
: att_name(n), att_coll(coll), att_health(100), att_gravity(Vector3f(0, -0.3, 0)), att_dir(Vector3f(0.0f, 0.0f, 0.0f)), 
att_doesLand(0), att_isColliding(0), att_isSprinting(0), att_sprintSpeed(0.4), att_speed(0.2), att_mouseSpeed(0.2), att_stamina(20), att_score(0) {
	att_cam.setLocation(att_coll.att_center);
	att_cam.setSpeed(att_speed, att_mouseSpeed);
}

void Player :: update(std :: vector <CollisionPlane> &collPlane) {
	if (att_dir.att_y >= att_gravity.att_y)
		att_dir.att_y += att_gravity.att_y;
	setPos(att_coll.att_center + att_dir);

	Vector3f pos = att_cam.getLoc();
	CollisionSphere tmp(pos, att_coll.att_radius);
	for (unsigned int i = 0 ; i < collPlane.size() ; ++i)
		Collision :: spherePlane(tmp, collPlane[i]);
	if (att_cam.getLoc().att_y < tmp.att_center.att_y)
		att_doesLand = true;
	else 
		att_doesLand = false;
	setPos(pos);
}

void Player ::display() {

}

std :: string &Player :: getName() {
	return att_name;
}

int Player :: getHealth() {
	return att_health;
}

CollisionSphere &Player :: getSphere() {
	return att_coll;
}

int Player :: getScore() {
	return att_score;
}

void Player :: addHealth(int h) {
	att_health += h;
}

void Player :: addScore(int p) {
	att_score += p;
}

void Player :: setPos(const Vector3f &pos) {
	att_coll.att_center = pos;
	att_cam.setLocation(pos);
}

Player :: ~Player() {}
