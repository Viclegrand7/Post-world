#include "GrE_Weapon.hh"

void Graphic :: Weapon :: draw(bool isInHands) {
	if (!isInHands)
		return;
	glPushMatrix(); //Saves previous Matrix

	glLoadIdentity();							//To get the right position, independant of where we were
	glTranslatef(att_defPosition.att_x, att_defPosition.att_y, att_defPosition.att_z); 	//Get to right position
	glRotatef(att_rotation.att_x,	1.0f, 0.0f, 0.0f);
	glRotatef(att_rotation.att_y,	0.0f, 1.0f, 0.0f);							//Rotations
	glRotatef(att_rotation.att_z,	0.0f, 0.0f, 1.0f);
	glCallList(att_currentFrame < att_frames.size() ? att_frames[att_currentFrame] : att_outerLook); //Draws
	//We draw the current frame. If we are passed the size of our frames, then that means the weapon is not equipped and we need to use outerLook

	glPopMatrix(); //Back to the saved Matrix
}

void Graphic :: Weapon :: draw(const Vector3f &position) {
	glPushMatrix(); //Saves previous Matrix

	glLoadIdentity();							//To get the right position, independant of where we were
	glTranslatef(position.att_x, position.att_y, position.att_z); 	//Get to right position
	glRotatef(att_rotation.att_x,	1.0f, 0.0f, 0.0f);
	glRotatef(att_rotation.att_y,	0.0f, 1.0f, 0.0f);							//Rotations
	glRotatef(att_rotation.att_z,	0.0f, 0.0f, 1.0f);
	glCallList(att_currentFrame < att_frames.size() ? att_frames[att_currentFrame] : att_outerLook); //Draws
	//We draw the current frame. If we are passed the size of our frames, then that means the weapon is not equipped and we need to use outerLook

	glPopMatrix(); //Back to the saved Matrix
}

bool Graphic :: Weapon :: update(bool isAutoAndAttacking) { //Will return true when is done with an animation
	++att_currentFrame;
	if (att_currentFrame == att_normalAnimation) {//End of normal animation
		att_currentFrame = 0; 	//We get to the beginning of normal animation
		return true;
	}
	else if (att_currentFrame == att_normalAnimation + att_attackAnimation) {//End of firing animation
		if (isAutoAndAttacking)
			att_currentFrame = att_normalAnimation; //Back to shooting
		else 
			att_currentFrame = 0;	//Going back to normal animation, not shooting anymore
		return true;
	}
	else if (att_currentFrame == att_normalAnimation + att_attackAnimation + att_secondaryAnimation) {//Finished with secondAnimation (reload/strong attack)
		att_currentFrame = 0;	//Done with secondAnimation, back to normal animation
		return true;
	}
	else if (att_currentFrame > att_frames.size()) {	//We are displaying a weapon not in anyone's hands
		att_currentFrame = att_frames.size();
		++att_rotation.att_y;
	}
	return false;
}

bool Graphic :: Weapon :: Grattack() {
	if (!att_currentFrame) {
		att_currentFrame = att_normalAnimation; //Beginning of attack animation
		return true;
	}
	return false;
}

bool Graphic :: Weapon :: Grreload() {return false;}//Gun knows how to reload. We pretend being melee: NOTHING to be done

bool Graphic :: Weapon :: Grsecondary() {//Gun knows how to aim. We pretend being melee: Strong attack
	if (!att_currentFrame) {
		att_currentFrame = att_normalAnimation + att_normalAnimation;
		return true;
	}
	return false;
}
