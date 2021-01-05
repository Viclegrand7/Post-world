#include "GrE_Item.hh"

// void Graphic :: Item :: draw() {
// 	glPushMatrix(); //Saves previous Matrix

// 	glTranslatef(att_position.att_x, att_position.att_y, att_position.att_z);
// 	glRotatef(att_rotation.att_x,	1.0f, 0.0f, 0.0f);
// 	glRotatef(att_rotation.att_y,	0.0f, 1.0f, 0.0f);
// 	glRotatef(att_rotation.att_z,	0.0f, 0.0f, 1.0f);
// 	glCallList(att_outerLook); //Draws

// 	glPopMatrix(); //Back to the saved Matrix
// }

Graphic :: Item :: Item(GLuint look, const Vector3f &position, const Vector3f &rotation) 
		: att_outerLook(look), att_position(position), att_rotation(rotation) {}


void Graphic :: Item :: setLocation(const Vector3f &pos) {
	att_position = pos;
}

void Graphic :: Item :: setRotation(const Vector3f &rot) {
	att_rotation = rot;
}
