#include "GrE_PowerUp.hh"

void Graphic :: PowerUp :: draw(const Vector3f &position) {
	glPushMatrix(); //Saves previous Matrix

	glTranslatef(position.att_x, position.att_y, position.att_z);
	glRotatef(att_rotation.att_x,	1.0f, 0.0f, 0.0f);
	glRotatef(att_rotation.att_y,	0.0f, 1.0f, 0.0f);
	glRotatef(att_rotation.att_z,	0.0f, 0.0f, 1.0f);
	glCallList(att_currentFrame == att_activationLook.size() ? att_outerLook : att_activationLook[att_currentFrame]); //Draws the right frame

	glPopMatrix(); //Back to the saved Matrix
}

bool Graphic :: PowerUp :: Grupdate(bool isPickedUp) {
	if (isPickedUp) {
		if (att_currentFrame++ == att_activationLook.size()) 	//We were displaying outerLook
			att_currentFrame = 0;								//Start the animation
		else if (att_currentFrame == att_activationLook.size())	//We are done with the animation
			return true;
	}
	else {
		att_rotation.att_y += att_rotation.att_y > 360.0f ? -360.0f : 1.0f; //Rotations
//	att_currentFrame = att_activationLook.size();  //When the bool returned will be taken into account (to stop displaying, for instance, no need to go to 0)
	}
	return false;
}
