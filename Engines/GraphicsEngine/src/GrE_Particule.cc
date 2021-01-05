#include "GrE_Particule.hh"
#include <chrono>

std::default_random_engine Graphic :: Particule :: att_generator(std::chrono::system_clock::now().time_since_epoch().count());

std::uniform_int_distribution<int> Graphic :: Particule :: att_distribution(-10,10);

void Graphic :: Particule :: draw() {
	glPushMatrix(); //Saves previous Matrix

	glTranslatef(att_position.att_x, att_position.att_y, att_position.att_z); 	//Get to right position
	glRotatef(att_rotation.att_x,	1.0f, 0.0f, 0.0f);
	glRotatef(att_rotation.att_y,	0.0f, 1.0f, 0.0f);								//Rotations
	glRotatef(att_rotation.att_z,	0.0f, 0.0f, 1.0f);
	glCallList(att_visual); //Draws
	//Maybe scale it?

	glPopMatrix(); //Back to the saved Matrix
}



bool Graphic :: Particule :: update() {
	if (!--att_length)
		return true;
	att_position += att_direction;
	att_rotation += att_rotationAdd;
	return false;
}
