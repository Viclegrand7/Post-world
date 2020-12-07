#ifndef RV_ZD_ENTITY_H
#define RV_ZD_ENTITY_H
#include "Entity.hh"
#endif

Entity :: Entity(float x, float y, float z, SDL_Texture *texture) : att_vector(x,y,z), att_texture(texture) {
	att_curFrame.x = 0; att_curFrame.y = 0;
	att_curFrame.w = 0; att_curFrame.h = 0;
}

Entity :: Entity(Vector3f vector, SDL_Texture *texture) : att_vector(vector), att_texture(texture) {
	att_curFrame.x = 0; att_curFrame.y = 0;
	att_curFrame.w = 0; att_curFrame.h = 0;
}

SDL_Texture * Entity :: getTex() {
	return att_texture;
}

SDL_Rect Entity :: getCurFrame() {
	return att_curFrame;
}