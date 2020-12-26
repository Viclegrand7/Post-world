#ifndef RV_ZD_ENNEMY_H
#define RV_ZD_ENNEMY_H
#include "Ennemy.hh"
#endif

Ennemy :: Ennemy(const std :: vector <unsigned int> &anim, unsigned int walk, unsigned int attack, unsigned int death, int health, int damage, float speed, const CollisionSphere &cs)
	: att_frames(anim), att_walk(walk), att_attack(attack), att_death(death), att_curFrame(0), att_health(health), att_damage(damage),att_speed(speed), 
	att_isMoving(true), att_isAttacking(false), att_isDead(false), att_collSphere(cs) {}


bool Ennemy :: update(std :: vector <CollisionPlane> &cp, const Vector3f &playerLoc) {
	if (!att_isDead) {
		att_direction = playerLoc - att_collSphere.att_center;
		att_direction.normalize();

		Vector3f pos(att_collSphere.att_center);
		pos.att_y -= 0.3;
		if (!att_isAttacking)
			pos += att_direction * att_speed;
		CollisionSphere tmp(pos, att_collSphere.att_radius);
		for (unsigned int i = 0 ; i < cp.size() ; ++i)
			Collision :: spherePlane(tmp, cp[i]);
		setLocation(pos);

		att_rotation.att_y = std :: acos(att_direction.att_z);
		if (att_direction.att_x > 0)
			att_rotation.att_y = - att_rotation.att_y;
	}
	if (att_health <= 0 && !att_isDead) {
		att_isDead = true;
		att_isMoving = att_isAttacking = false;
		att_curFrame = att_walk + att_attack; //Sets animation to death
		return 1;
	}
	++att_curFrame;
	if (att_isMoving && att_curFrame >= att_walk)
		att_curFrame = 0;
	else if (att_isAttacking && att_curFrame >= att_walk + att_attack)
		att_curFrame = att_walk;
	else if (att_isDead && att_curFrame)
		att_curFrame = att_walk + att_attack + att_death - 1; //Stuck on last frame
	return 0;
}

void Ennemy :: display() {
	glPushMatrix(); //Saves prev Matrix

	glTranslatef(att_collSphere.att_center.att_x, att_collSphere.att_center.att_y, att_collSphere.att_center.att_z);
	glRotatef(-att_rotation.att_x * (180.0/M_PI), 1, 0, 0);
	glRotatef(-att_rotation.att_y * (180.0/M_PI), 1, 0, 0);
	glRotatef(-att_rotation.att_z * (180.0/M_PI), 1, 0, 0);
	glScalef(1.0f, 1.0f, 1.0f); //Allows for scaling
	glCallList(att_frames[att_curFrame]);

	glPopMatrix(); //Gets back to prev Matrix

}

bool Ennemy :: setAttack(CollisionSphere &player) {
	if (!att_isDead && Collision :: sphereSphere(player, att_collSphere)) {
		att_isAttacking = true;
		att_isMoving = false;
		return true;
	}
	else {		
		att_isAttacking = false;
		if (!att_isDead)
			att_isMoving = true;
		return false;
	}
}

CollisionSphere &Ennemy :: getCollSphere() {
	return att_collSphere;
}

void Ennemy :: setLocation(const Vector3f &loc) {
	att_collSphere.att_center = loc;
}

void Ennemy :: getHit(int dmg) {
	att_health -= dmg;
//////////////////////////////////////////////////////////////////////////////////
//	if (att_health <= 0)
//		att_isDead = true;
//////////////////////////////////////////////////////////////////////////////////
}

int Ennemy :: getHealth() {
	return att_health;
}

int Ennemy :: getDamage() {
	return att_damage;
}

bool Ennemy :: isDead() {
	return att_isDead;
}