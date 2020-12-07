#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

namespace utility {
	inline float timeInSeconds() {
		float t = SDL_GetTicks();
		t *= 0.001;
		return t;
	}
}