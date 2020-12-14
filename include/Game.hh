#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_SDL_IMAGE_H
#define RV_ZD_SDL_IMAGE_H
#include <SDL2/SDL_image.h>
#endif

#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_STRING
#define RV_ZD_STRING
#include <string>
#endif

#ifndef RV_ZD_CAMERA_H
#define RV_ZD_CAMERA_H
#include "Camera.hh"
#endif

#ifndef RV_ZD_LOADER_H
#define RV_ZD_LOADER_H
#include "Loader.hh"
#endif

#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif

#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif

#ifndef RV_ZD_RENDER_H
#define RV_ZD_RENDER_H
#include "Render.hh"
#endif

#ifndef RV_ZD_LEVEL_H
#define RV_ZD_LEVEL_H
#include "Level.hh"
#endif

#ifndef RV_ZD_PLAYER_H
#define RV_ZD_PLAYER_H
#include "Player.hh"
#endif






class Game {
	Objloader att_obj;
	Render att_render;
	std :: vector <Level *> att_levels;
	int att_fps;
	std :: vector <Entity> att_entities;
	Player *att_player;

	void initskybox(std :: vector <Entity> &entities, SDL_PixelFormat *);

	void update();
	void display();
//	unsigned int loadTexture(const char *filename);
//	void loadAnimation(const std :: vector <unsigned int> &anim, const std :: string &filename, int frames);
public:
	Game(SDL_DisplayMode);
	~Game();
	void run();
};