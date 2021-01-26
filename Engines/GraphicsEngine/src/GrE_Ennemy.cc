#include "GrE_Ennemy.hh"

void Graphic :: Ennemy :: draw(const Vector3f &pos, const Vector3f &rot) {
	glPushMatrix(); //Saves previous Matrix

	glTranslatef(pos.att_x, pos.att_y, pos.att_z); 	//Get to right position
	glRotatef(rot.att_x,	1.0f, 0.0f, 0.0f);
	glRotatef(rot.att_y,	0.0f, 1.0f, 0.0f);								//Rotations
	glRotatef(rot.att_z,	0.0f, 0.0f, 1.0f);
	glCallList(att_frames[att_currentFrame]); //Draws the current frame

	glPopMatrix(); //Back to the saved Matrix
}

bool Graphic :: Ennemy :: update() {
	++att_currentFrame;
	if (att_doesDie && att_currentFrame <= att_walkAnimation + att_attackAnimation) {//We are not dying yet
		att_currentFrame = att_walkAnimation + att_attackAnimation; //Beginning of death
		return false;
	}
	if (att_doesAttack) {
		att_currentFrame = att_walkAnimation; //Beginning of attackAnimation
		return false;
	}
	if (att_currentFrame == att_walkAnimation) {//End of normal animation
		att_currentFrame = 0; 	//We get to the beginning of normal animation
		return false;
	}
	if (att_currentFrame == att_walkAnimation + att_attackAnimation) {//End of attacking animation
		att_currentFrame = 0;
		return false;
	}
	if (att_currentFrame == att_frames.size()) {
		return true; //He just died
	}
	return false;
}

void Graphic :: Ennemy :: die() {
	att_doesAttack = false;
	att_doesDie = true;
}

bool Graphic :: Ennemy :: attack() {
	if (att_doesDie)
		return false;
	att_doesAttack = true;
	return true;
}

