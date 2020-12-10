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

#ifndef RV_ZD_ENTITY_H
#define RV_ZD_ENTITY_H
#include "Entity.hh"
#endif



class Render {
	SDL_Window *att_window;
	SDL_Renderer *att_renderer;
public:
	Render(const char *title, int width, int height);
	SDL_Texture* loadTexture(const char* filePath);

	int getRefreshRate();

	void cleanUp();
	void clear();
	void render(Entity &entity);
	void display();
	~Render();
};