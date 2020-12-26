#ifndef RV_ZD_MAP_H
#define RV_ZD_MAP_H
#include "Map.hh"
#endif

Map :: Map(unsigned int left, unsigned int back, unsigned int right, unsigned int front, unsigned int roof, unsigned int floor, float att_size)
: att_size(att_size) {
	att_faces[0] = left;
	att_faces[1] = back;
	att_faces[2] = right;
	att_faces[3] = front;
	att_faces[4] = roof;
	att_faces[5] = floor;
}

Map :: ~Map() {
	glDeleteTextures(6, &att_faces[0]);
}

void Map :: drawMap() {
	if (att_size == -1)
		return;
	bool b1=glIsEnabled(GL_TEXTURE_2D);	//new, we left the textures turned on, if it was turned on
	bool b2=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);	//turn off lighting, when making the map
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,att_faces[0]);	//use the texture we want
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glTexCoord2f(0,0);	//use the correct texture vector3d
		glVertex3f(att_size/2,att_size/2,att_size/2);	//and a vertex
		glTexCoord2f(1,0);	//and repeat it...
		glVertex3f(-att_size/2,att_size/2,att_size/2);
		glTexCoord2f(1,1);
		glVertex3f(-att_size/2,-att_size/2,att_size/2);
		glTexCoord2f(0,1);
		glVertex3f(att_size/2,-att_size/2,att_size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,att_faces[1]);
	glBegin(GL_QUADS);	
		//left face
		glTexCoord2f(0,0);
		glVertex3f(-att_size/2,att_size/2,att_size/2);
		glTexCoord2f(1,0);
		glVertex3f(-att_size/2,att_size/2,-att_size/2);
		glTexCoord2f(1,1);
		glVertex3f(-att_size/2,-att_size/2,-att_size/2);
		glTexCoord2f(0,1);
		glVertex3f(-att_size/2,-att_size/2,att_size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,att_faces[2]);
	glBegin(GL_QUADS);	
		//front face
		glTexCoord2f(1,0);
		glVertex3f(att_size/2,att_size/2,-att_size/2);
		glTexCoord2f(0,0);
		glVertex3f(-att_size/2,att_size/2,-att_size/2);
		glTexCoord2f(0,1);
		glVertex3f(-att_size/2,-att_size/2,-att_size/2);
		glTexCoord2f(1,1);
		glVertex3f(att_size/2,-att_size/2,-att_size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,att_faces[3]);	
	glBegin(GL_QUADS);	
		//right face
		glTexCoord2f(0,0);
		glVertex3f(att_size/2,att_size/2,-att_size/2);
		glTexCoord2f(1,0);
		glVertex3f(att_size/2,att_size/2,att_size/2);
		glTexCoord2f(1,1);
		glVertex3f(att_size/2,-att_size/2,att_size/2);
		glTexCoord2f(0,1);
		glVertex3f(att_size/2,-att_size/2,-att_size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,att_faces[4]);		
	glBegin(GL_QUADS);			//top face
		glTexCoord2f(1,0);
		glVertex3f(att_size/2,att_size/2,att_size/2);
		glTexCoord2f(0,0);
		glVertex3f(-att_size/2,att_size/2,att_size/2);
		glTexCoord2f(0,1);
		glVertex3f(-att_size/2,att_size/2,-att_size/2);
		glTexCoord2f(1,1);
		glVertex3f(att_size/2,att_size/2,-att_size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,att_faces[5]);		
	glBegin(GL_QUADS);	
		//bottom face
		glTexCoord2f(1,1);
		glVertex3f(att_size/2,-att_size/2,att_size/2);
		glTexCoord2f(0,1);
		glVertex3f(-att_size/2,-att_size/2,att_size/2);
		glTexCoord2f(0,0);
		glVertex3f(-att_size/2,-att_size/2,-att_size/2);
		glTexCoord2f(1,0);
		glVertex3f(att_size/2,-att_size/2,-att_size/2);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
	if(b2)
		glEnable(GL_LIGHTING);	//turn everything back, which we turned on, and turn everything off, which we have turned on.
	//	std::cout << "called" << std::endl;
}