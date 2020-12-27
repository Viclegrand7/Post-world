#ifndef RV_ZD_WEAPON_H
#define RV_ZD_WEAPON_H
#include "Weapon.hh"
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif

#ifndef RV_ZD_GLU_H
#define RV_ZD_GLU_H
#include <GL/glu.h>
#endif



#include <cstdlib> //random

///////////////////////////////////////////////////////////////////////////////////////////////
Uint8 TEST_UP_Key = SDL_SCANCODE_U;
Uint8 TEST_DOWN_Key = SDL_SCANCODE_J;
Uint8 TEST_LEFT_Key = SDL_SCANCODE_H;
Uint8 TEST_RIGHT_Key = SDL_SCANCODE_L;
Uint8 TEST_TILT_LEFT_Key = SDL_SCANCODE_Y;
Uint8 TEST_TILT_RIGHT_Key = SDL_SCANCODE_I;
///////////////////////////////////////////////////////////////////////////////////////////////


Weapon :: Weapon(std :: vector <unsigned int> &animation, unsigned int look, unsigned int normal, unsigned int fire, unsigned int reload, bool isAuto, Vector3f pos, 
	Vector3f rot, Vector3f aimPos, Vector3f aimRot, float prec, float aimPrec, unsigned int dmg, unsigned int maxB, unsigned int allB, unsigned int speed, const std :: string &name)
: att_frames(animation), att_look(look), att_animation(normal), att_fire(fire), att_reload(reload), att_positionExp(pos), att_rotationExp(rot), att_position(pos), 
	att_rotation(rot), att_positionAim(aimPos), att_rotationAim(aimRot), att_curPos(pos), att_curRot(rot), att_precision(prec ? prec : 0.000001f), 
	att_aimPrecision(aimPrec ? aimPrec : 0.000001f), att_damage(dmg), att_isAim(false), att_isReloading(false), att_isAuto(isAuto), att_isFiring(false), att_isTest(true), 
	att_magazine(maxB), att_magazineMax(maxB), att_curBullets(allB), att_maxBullets(allB), att_lastShot(-1000), att_speed(speed), att_curFrame(0), att_curMode(1), att_name(name) {}
Weapon :: ~Weapon() {

}


void Weapon :: update() {
	test();
	++att_lastShot;
	++att_curFrame;
	if (att_curMode == 1) { //Not doing anything
		if (att_curFrame >= att_animation) //End of normal animation
			att_curFrame = 0; //We get to the beginning of normal animation
	}
	else if (att_curMode == 2) { //Shooting
		if (att_curFrame >= att_animation + att_fire) { //End of firing animation
			att_curMode = 1;
			att_curFrame = 0; //Going back to normal animation, not shooting anymore
		}
	}
	else if (att_curFrame >= att_animation + att_fire + att_reload) { //Ended reloading
			att_curMode = 1;
			att_curFrame = 0;
			att_isReloading = false;
	}

	Vector3f tmpVec(att_positionExp - att_curPos); //Where we should go
	tmpVec.normalize();
	tmpVec *= 0.3f; //Sensibility? Should have an option for that, honestly
	att_curPos += tmpVec;
	if (std :: abs(att_positionExp.att_x - att_curPos.att_x) < 0.3 && std :: abs(att_positionExp.att_y - att_curPos.att_y) < 0.3 && std :: abs(att_positionExp.att_z - att_curPos.att_z) < 0.3)
		att_curPos = att_positionExp; //From what I understood this avoids infinite loop. Not sure why or how

	tmpVec = att_rotationExp - att_curRot; //Where we should rotate
	tmpVec.normalize();
	tmpVec *= 0.3f; //Sensibility? Should have an option for that, honestly
	att_curRot += tmpVec;
	if (std :: abs(att_curRot.att_x - att_rotationExp.att_x) < 0.3 && std :: abs(att_curRot.att_y - att_rotationExp.att_y) < 0.3 && std :: abs(att_curRot.att_z - att_rotationExp.att_z) < 0.3)
		att_curRot = att_rotationExp; //From what I understood this avoids infinite loop. Not sure why or how
}

void Weapon :: show() {
	glPushMatrix(); //Saves prev Matrix

	glTranslatef(att_curPos.att_x, att_curPos.att_y, att_curPos.att_z);
	glRotatef(att_curRot.att_x, 1, 0, 0);
	glRotatef(att_curRot.att_y, 0, 1, 0);
	glRotatef(att_curRot.att_z, 0, 0, 1);
	glCallList(att_frames[att_curFrame]);

	glPopMatrix(); //Gets back to prev Matrix
}

bool Weapon :: fire(Vector3f &dir, const Vector3f &camDir) {
	if (att_isReloading)
		return false;
	if (att_lastShot >= att_speed && ((!att_isAuto && !att_isFiring) || att_isAuto)) {
		if (att_magazine) {
			if (att_isAim) {
				dir.att_x = camDir.att_x + (float) (rand() % 3 - 1) / att_aimPrecision;
				dir.att_y = camDir.att_y + (float) (rand() % 3 - 1) / att_aimPrecision; //Random shot. Pretty dumb way of doing it. Will have 1/27 of shooting correctly with bad precision
				dir.att_z = camDir.att_z + (float) (rand() % 3 - 1) / att_aimPrecision;
			}
			else {
				dir.att_x = camDir.att_x + (float) (rand() % 3 - 1) / att_precision;
				dir.att_y = camDir.att_y + (float) (rand() % 3 - 1) / att_precision; //Random shot. Pretty dumb way of doing it. Will have 1/27 of shooting correctly with bad precision
				dir.att_z = camDir.att_z + (float) (rand() % 3 - 1) / att_precision;
			}
			att_isFiring = true;
			att_lastShot = 0;
			--att_magazine;
			--att_curBullets;
			att_curFrame = att_animation; //Starting fire animation
			att_curMode = 2;
			return true;
		}
		else {
			reload(); //We shot with empty mag => reloading
			return false;
		}
	}
	return false;
}

void Weapon :: stopFire() {
	att_isFiring = false;
}

void Weapon :: reload() {
	if (!att_isReloading && att_magazine < att_magazineMax && att_curBullets && att_curBullets != att_magazine) {
	//If we: Aren't reloading, don't have max bullets, have spare bullets
		att_isReloading = true;
		if (att_curBullets > att_magazineMax) { //We have more than 1 mag available
			att_magazine = att_magazineMax;
		}
		else {
			att_magazine = att_curBullets;
		}
		att_curFrame = att_animation + att_fire; 	//Reloading animation
		att_curMode = 3;							//We are reloading
	}
}

void Weapon :: aim() {
	att_isAim = !att_isAim; //We revert, no matter what it was
	if (att_isAim) {
		att_positionExp = att_positionAim;
		att_rotationExp = att_rotationAim;
	}
	else {
		att_positionExp = att_position;
		att_rotationExp = att_rotation;
	}
}

void Weapon :: test() {
	if (att_isTest) {
		const Uint8 *keys(SDL_GetKeyboardState(NULL));
		if (keys[TEST_LEFT_Key])
			att_positionExp.att_x -= 0.02;
		if (keys[TEST_RIGHT_Key])
			att_positionExp.att_x += 0.02;
		if (keys[TEST_UP_Key])
			att_positionExp.att_y += 0.02;
		if (keys[TEST_DOWN_Key])
			att_positionExp.att_y -= 0.02;

		if (keys[TEST_TILT_LEFT_Key])
			att_rotationExp.att_y -= 0.2;
		if (keys[TEST_TILT_RIGHT_Key])
			att_rotationExp.att_y += 0.2;
	}
}

void Weapon :: addB(unsigned int num) {
	att_curBullets = att_curBullets + num > att_maxBullets ? att_maxBullets : att_curBullets + num;
}

void Weapon :: setB(unsigned int num) {
	att_curBullets = num > att_maxBullets ? att_maxBullets : num;
}

int Weapon :: getDmg() {
	return att_damage;
}

unsigned int Weapon :: getAmmo() {
	return att_magazine;
}

unsigned int Weapon :: getAllAmmo() {
	return att_curBullets;
}

std :: string Weapon :: getName() {
	return att_name;
}

std :: vector <unsigned int> &Weapon :: getAnimation() {
	return att_frames;
}

bool Weapon :: isAim() {
	return att_isAim;
}

unsigned int Weapon :: getLook() {
	return att_look;
}