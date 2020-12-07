#include "Render.hh"

Render :: Render(const char *title, int width, int height) : att_window(NULL) {

	if (!(att_window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN))) {
		std :: cerr << "Failed creating window: " << SDL_GetError() << "\n";
		throw "Failed creating window \n";
	}

	att_renderer = SDL_CreateRenderer(att_window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* Render :: loadTexture(const char* filePath) {
	SDL_Texture *texture(NULL);
	texture = IMG_LoadTexture(att_renderer, filePath);
	if (texture == NULL)
		std :: cerr << "Failed loading texture. " << SDL_GetError() << "\n";
	return texture;
}

void Render :: cleanUp() {
	SDL_DestroyWindow(att_window);
}

inline void Render :: clear() {
	SDL_RenderClear(att_renderer); //Currently hating this, better call the function everytime
}

inline void Render :: render(SDL_Texture *texture) {
	SDL_Rect source;
	source.x = 0; source.y = 0; //Starting at top left of the image 
	source.w = 32; source.h = 32; //Using some size

	SDL_Rect destination;
	destination.x = 0; destination.y = 0; //Starts top left
	destination.w = 32; destination.h = 32; //Where it ends

	SDL_RenderCopy(att_renderer, texture, &source, &destination); //Last 2 pointers: How gig source is, destination (transformations)
}

inline void Render :: display() {
	SDL_RenderPresent(att_renderer); //Same
}