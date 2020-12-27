#ifndef RV_ZD_PLAYER_H
#define RV_ZD_PLAYER_H
#include "Player.hh"
#endif

extern bool NO_GRAVITY;



Player :: Player(const char* n, const CollisionSphere &coll, Weapon *weapon) 
: att_name(n), att_coll(coll), att_health(100), att_gravity(Vector3f(0, -0.3, 0)), att_dir(Vector3f(0.0f, 0.0f, 0.0f)), att_doesLand(0), att_isColliding(0), 
	att_isSprinting(0), att_sprintSpeed(0.6), att_speed(0.2), att_mouseSpeed(0.2), att_stamina(30), att_staminaMax(50), att_score(0), att_head(0), att_curWeapon(0) {
	att_cam.setLocation(att_coll.att_center);
	att_cam.setSpeed(att_speed, att_mouseSpeed);
	att_weapons.push_back(weapon);
}

void Player :: update(std :: vector <CollisionPlane> &collPlane) {
	if (att_dir.att_y >= att_gravity.att_y && !NO_GRAVITY)
		att_dir.att_y += att_gravity.att_y;

	Vector3f pos(att_cam.getLoc() + att_dir); //Applying gravity to temp
	CollisionSphere tmp(pos, att_coll.att_radius);
	Vector3f oldPos(pos);
	for (unsigned int i = 0 ; i < collPlane.size() ; ++i)
		Collision :: spherePlane(tmp, collPlane[i]);
																std :: cout << "Before calculation: " << oldPos << " | After : " << tmp.att_center << " | try : " << pos << std :: endl;
	if (oldPos.att_y < tmp.att_center.att_y)
		att_doesLand = true;
	setPos(pos);

	att_weapons[att_curWeapon]->update();

	if (att_isSprinting)
		att_stamina -= 0.5f;
	else {
		att_stamina += 0.125f;
		att_stamina = att_stamina > att_staminaMax ? att_staminaMax : att_stamina;
	}

	if (att_cam.isMoving()) { //Between 0 and 9, head goes up-right. 10 and 19, head goes bot-right. 20-29, bot-left. 30-39 : up-left
		if (att_head < 40)
			++att_head;
		else 
			att_head = 0;
	
		if (att_head < 10) {
			att_cam.lookAt(att_cam.getPitch() + (att_head - 10) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting), att_cam.getYaw() + (att_head - 10) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting) );
		}
		else if (att_head < 20) {
			att_cam.lookAt(att_cam.getPitch() + (10 - att_head) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting), att_cam.getYaw() + (att_head - 10) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting));
		}
		else if (att_head < 30) {
			att_cam.lookAt(att_cam.getPitch() + (10 - att_head) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting), att_cam.getYaw() + (10 - att_head) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting));
		}
		else {
			att_cam.lookAt(att_cam.getPitch() + (att_head - 10) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting), att_cam.getYaw() + (10 - att_head) * (0.0078125f * !att_isSprinting + 0.03125f * att_isSprinting));
		}
	// /128 if walking, /32 if running
	}
}

void Player :: display() {
	att_weapons[att_curWeapon]->show();
}

void Player :: jump() {
	if (att_doesLand) {
		att_dir.att_y += 1.5f;
		att_doesLand = false;
	}
}

void Player :: sprint() {
	if (att_stamina > 0.5f) {
		att_isSprinting = true;
		att_cam.setSpeed(att_sprintSpeed, att_mouseSpeed);
	}
	else {
		att_isSprinting = false;
	}
}

void Player :: noSprint() {
	att_isSprinting = false;
	att_cam.setSpeed(att_speed, att_mouseSpeed);
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


void Player :: addWeapon(Weapon *weapon) {
	att_weapons.push_back(weapon);
}

void Player :: changeWeapon(unsigned int num) {
	if (num < att_weapons.size())
		att_curWeapon = num;
}

void Player :: nextWeapon() {
	++att_curWeapon;
	if (att_curWeapon >= att_weapons.size())
		att_curWeapon = 0;
}

void Player :: prevWeapon() {
	--att_curWeapon;
	if (att_curWeapon >= att_weapons.size())
		att_curWeapon = att_weapons.size() - 1;
}

Weapon *Player :: getCurWeapon() {
	return att_weapons[att_curWeapon];
}


Player :: ~Player() {}
