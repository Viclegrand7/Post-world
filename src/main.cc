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

#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_Render_H //Let's make sure we don't write same thing multiple times
#define RV_ZD_Render_H //Equivalent to #pragma once? Thought pragma worked only on Windows and not the others...
#include "Render.hh"
#endif

#ifndef RV_ZD_ENTITY_H
#define RV_ZD_ENTITY_H
#include "Entity.hh"
#endif

#ifndef RV_ZD_UTILITY_H
#define RV_ZD_UTILITY_H
#include "Utility.hh"
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

	SDL_DisplayMode DisplayMode; //Will allow to get resolution, in theory
	SDL_GetCurrentDisplayMode(0, &DisplayMode); //Stocking datas in DisplayMode

	Render window("Best_Game v0.0", DisplayMode.w, DisplayMode.h); //Creating window having the right size(?) and located on coordinated 0,0 (wherever that is)
	//If those don't do perfect job, getDisplayBounds should do the work (need to know the number of monitor? => NOW I KNOW IT! Render, getRefreshRate() has it)

	int refreshRate = window.getRefreshRate();

	std :: cout << refreshRate << std :: endl; //I get 30... issue on my side?

//	SDL_Texture *imaginaryTexture = window.loadTexture("../res/img/someImage.png");

	std::vector<Entity> entities; //Needs textures

	SDL_Texture *background = window.loadTexture("../res/img/Background.png");
	entities.push_back(Entity(Vector3f(0,0,0), background));
/*
	{
		Entity platform0(Vector3f(100, 0, 0), imaginaryTexture);
		entities.push_back(platform0);
	} //Adding those creat a scope, ensuring platform0 gets deleted afterwards. Same than entities.pushback(Entity(Vector3f(100, 0, 0), imaginaryTexture))?
*/
	bool isRunning = true;
	const float timeStep(0.01f); //FPS = 100
	float accumulator(0.0f);
	float currentTime(utility :: timeInSeconds());
/*
	const int FPS(100);
	unsigned int currentTime(0); //FPS regulation
*/
	unsigned int currentTimeTick(0); //FPS regulation

	SDL_Event event;

	while (isRunning) {
		currentTimeTick = SDL_GetTicks();
		float newTime = utility :: timeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= timeStep) {
			while (SDL_PollEvent(&event))
				switch (event.type) {
					case SDL_QUIT :
					isRunning = false;
					break;
				}
			accumulator -= timeStep; 
		}

		const float alpha = accumulator / timeStep; //Percent of how much we need to go until 

		window.clear();
		for (Entity &someone : entities)
			window.render(someone);
//		window.render(platform0);
		window.display();

		if (1000./refreshRate > SDL_GetTicks() - currentTimeTick)
			SDL_Delay(1000/refreshRate - (SDL_GetTicks() - currentTimeTick)); //FPS regulation based on how fast monitor can go

	}

	window.cleanUp();
	SDL_Quit();

	return 0;		
}