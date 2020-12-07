#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_SDL_IMAGE_H
#define RV_ZD_SDL_IMAGE_H
#include <SDL2/SDL_image.h>
#endif

#ifndef RV_ZD_SDL_MIXER_H
#define RV_ZD_SDL_MIXER_H
#include <SDL2/SDL_mixer.h>
#endif

#ifndef RV_ZD_SDL_TTF_H
#define RV_ZD_SDL_TTF_H
#include <SDL2/SDL_ttf.h>
#endif

#ifndef RV_ZD_IOSTREAM
#define RV_ZD_IOSTREAM
#include <iostream>
#endif

#ifndef RV_ZD_STRING
#define RV_ZD_STRING
#include <string>
#endif

#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif


class Entity {
	Vector3f att_vector;
	SDL_Rect att_curFrame;
	SDL_Texture *att_texture;
public:
//	Entity(float x, float y);
	Entity(float x, float y, float z, SDL_Texture *texture);
	Entity(Vector3f vector, SDL_Texture *texture);
	Vector3f &getVector() {return att_vector;}
	SDL_Texture *getTex();
	SDL_Rect getCurFrame();
};