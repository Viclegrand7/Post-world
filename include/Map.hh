#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif

#ifndef RV_ZD_GLU_H
#define RV_ZD_GLU_H
#include <GL/glu.h>
#endif





class Map {
	unsigned int att_faces[6];
	float att_size;
public:
	Map(unsigned int left = -1, unsigned int back = -1, unsigned int right = -1, unsigned int front = -1, unsigned int roof = -1, unsigned int floor = -1, float size = -1);
	~Map();
	void drawMap();	
};