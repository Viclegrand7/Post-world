#include "GrE_Weapon.hh"

void Graphic :: Weapon :: draw() {
	glPushMatrix(); //Saves previous Matrix

	glLoadIdentity();							//To get the right position, independant of where we were
	glTranslatef(att_position.att_x, att_position.att_y, att_position.att_z); 	//Get to right position
	glRotatef(att_rotation.att_x,	1.0f, 0.0f, 0.0f);
	glRotatef(att_rotation.att_y,	0.0f, 1.0f, 0.0f);							//Rotations
	glRotatef(att_rotation.att_z,	0.0f, 0.0f, 1.0f);
	glCallList(att_currentFrame < att_frames.size() ? att_frames[att_currentFrame] : att_outerLook); //Draws
	//We draw the current frame. If we are passed the size of our frames, then that means the weapon is not equipped and we need to use outerLook

	glPopMatrix(); //Back to the saved Matrix
}

bool Graphic :: Weapon :: update(bool isAutoAndAttacking) { //Will return true when is done with an animation
	++att_currentFrame;
	std :: cout << "att_currentFrame: " << att_currentFrame << std :: endl;
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

void Graphic :: Weapon :: attack() {
	att_currentFrame = att_normalAnimation; //Beginning of attack animation
}

void Graphic :: Weapon :: reload() {}//Gun knows how to reload. We pretend being melee: NOTHING to be done

void Graphic :: Weapon :: secondary() {//Gun knows how to aim. We pretend being melee: Strong attack
	att_currentFrame = att_normalAnimation + att_normalAnimation;
}
