#ifndef RV_ZD_GAME_H
#define RV_ZD_GAME_H
#include "Game.hh"
#endif



/*
	att_render.makeRenderer("Best_Game v0.0", DisplayMode.w, DisplayMode.h); //Creating window having the right size(?) and located on coordinated 0,0 (top left)
	//If those don't do perfect job, getDisplayBounds should do the work (need to know the number of monitor? => NOW I KNOW IT! Render, getRefreshRate() has it)
*/



int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std :: cerr << "Failed initialising: " << SDL_GetError() << "\n";
		throw "Failed initialising \n";
	}

	if (!IMG_Init(IMG_INIT_PNG)) {
		std :: cerr << "Failed initialising PNG: " << SDL_GetError() << "\n";
		throw "Failed initialising PNG\n";
	}

	SDL_DisplayMode DisplayMode; //Will allow to get resolution, in theory
	SDL_GetCurrentDisplayMode(0, &DisplayMode); //Stocking datas in DisplayMode

	Game game(DisplayMode);
	game.run();

	return 0;		
}