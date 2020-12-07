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


int Render :: getRefreshRate() {
	int whichScreen = SDL_GetWindowDisplayIndex(att_window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(whichScreen, 0, &mode);

	return mode.refresh_rate;
}


void Render :: cleanUp() {
	SDL_DestroyWindow(att_window);
}

void Render :: clear() {
	SDL_RenderClear(att_renderer); //Currently hating this, better call the function everytime
}

void Render :: render(Entity &entity) {
	SDL_Rect source;
	source.x = entity.getCurFrame().x; source.y = entity.getCurFrame().y; //Starting at top left of the image 
	source.w = entity.getCurFrame().w; source.h = entity.getCurFrame().h; //Using some size

	SDL_Rect destination;
	destination.x = entity.getVector().att_x; destination.y = entity.getVector().att_y; //Starts where we wanted it to be
	destination.w = entity.getCurFrame().w; destination.h = entity.getCurFrame().h; //Where it ends (its size later)

	SDL_RenderCopy(att_renderer, entity.getTex(), &source, &destination); //Last 2 pointers: How big source is, destination (transformations)
}

void Render :: display() {
	SDL_RenderPresent(att_renderer);
}