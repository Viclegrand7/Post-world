#ifndef RV_ZD_RENDER_H
#define RV_ZD_RENDER_H
#include "Render.hh"
#endif



Render :: Render(const char *title, int width, int height) : att_window(NULL), att_renderer(NULL) {

	if (!(att_window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL))) {
//	if (!(att_window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN))) {
		std :: cerr << "Failed creating window: " << SDL_GetError() << "\n";
		throw "Failed creating window \n";
	}

	att_format = SDL_GetWindowSurface(att_window)->format;

	att_renderer = SDL_CreateRenderer(att_window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* Render :: loadTexture(const char* filePath) {
	SDL_Texture *texture(NULL);
	texture = IMG_LoadTexture(att_renderer, filePath);
	if (texture == NULL)
		std :: cerr << "Failed loading texture. " << SDL_GetError() << "\n";
	return texture;
}


int Render :: getRefreshRate() const {
	int whichScreen = SDL_GetWindowDisplayIndex(att_window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(whichScreen, 0, &mode);

	return mode.refresh_rate;
}


SDL_PixelFormat * Render :: getFormat() const {
	return att_format;
}

bool Render :: isFull() const {
	return SDL_GetWindowFlags(att_window) & SDL_WINDOW_FULLSCREEN;
}


void Render :: cleanUp() {
	SDL_DestroyWindow(att_window);
}

void Render :: clear() {
	SDL_RenderClear(att_renderer);
}

void Render :: render(Entity &entity) {
	SDL_Rect source;
	source.x = entity.getCurFrame().x; source.y = entity.getCurFrame().y; //Starting at top left of the image 
	source.w = entity.getCurFrame().w; source.h = entity.getCurFrame().h; //Using some size

	SDL_Rect destination;
	destination.x = entity.getVector().att_x; destination.y = entity.getVector().att_y; //Starts where we wanted it to be

//	destination.w = entity.getCurFrame().w * 10; destination.h = entity.getCurFrame().h * 10; //Where it ends (its size later)

	SDL_GetWindowSize(att_window, &destination.w, &destination.h); //Allows to draw a background. Need to save and reuse somewhere
	//Entities could be inheriting in few classes: Background, objects and particles? (Particles useful for fire, blood, water,... May not be Entities though)
	//Particles don't have gravity/physic applying to it, may need to do it some other way


	SDL_RenderCopy(att_renderer, entity.getTex(), &source, &destination); //Last 2 pointers: How big source is, destination (transformations)
}

void Render :: display() {
	SDL_RenderPresent(att_renderer);
}

void Render :: getSizes(int &width, int &height) const {
	SDL_GetWindowSize(att_window, &width, &height);
}

SDL_Window *Render :: getWindow() const {
	return att_window;
}



Render :: ~Render() {
	if (att_renderer)
		SDL_DestroyRenderer(att_renderer);
}