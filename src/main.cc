#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_SDL_IMAGE_H
#define RV_ZD_SDL_IMAGE_H
#include <SDL2/SDL_image.h> //Image gestion?
#endif

#ifndef RV_ZD_SDL_MIXER_H
#define RV_ZD_SDL_MIXER_H
#include <SDL2/SDL_mixer.h> //Sound gestion/creation(?)?
#endif

#ifndef RV_ZD_SDL_TTF_H
#define RV_ZD_SDL_TTF_H
#include <SDL2/SDL_ttf.h> //Displaying text
#endif

#ifndef RV_ZD_IOSTREAM
#define RV_ZD_IOSTREAM
#include <iostream>
#endif

#ifndef RV_ZD_Render_H //Let's make sure we don't write same thing multiple times
#define RV_ZD_Render_H //Equivalent to #pragma once? Thought pragma worked only on Windows and not the others...
#include "Render.hh"
#endif

#ifndef RV_ZD_ENTITY_H
#define RV_ZD_ENTITY_H
#include "Entity.hh"
#endif

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std :: cerr << "Failed initialising: " << SDL_GetError() << "\n";
		throw "Failed initialising \n";
		return 1;
	}

	if (!IMG_Init(IMG_INIT_PNG)) {
		std :: cerr << "Failed initialising PNG: " << SDL_GetError() << "\n";
		throw "Failed initialising PNG\n";
		return 1;
	}

	unsigned int currentTime(0); //FPS regulation
	const int FPS(30);

	SDL_DisplayMode DisplayMode; //Will allow to get resolution, in theory
	SDL_GetCurrentDisplayMode(0, &DisplayMode); //Stocking datas in DisplayMode

	Render window("Best_Game v0.0", DisplayMode.w, DisplayMode.h); //Creating window having the right size(?) and located on coordinated 0,0 (wherever that is)
	//If those don't do perfect job, getDisplayBounds should do the work (need to know the number of monitor?)

	bool isRunning = true;

	SDL_Event event;

	while (isRunning) {
		currentTime = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;
		}

		if (1000./FPS > SDL_GetTicks() - currentTime)
			SDL_Delay(1000./FPS - (SDL_GetTicks() - currentTime)); //FPS regulation. atm 30 FPS max
	}

	window.cleanUp();
	SDL_Quit();

	return 0;		
}