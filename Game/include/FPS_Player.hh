#ifndef RV_ZD_FPSPLAYER
#define RV_ZD_FPSPLAYER

#include "GrE_Camera.hh"
#include "GrE_Player.hh"
#include "PhE_Player.hh"
#include "Player.hh"

namespace FPS {
	class Player : virtual public Graphic :: Player, ::Player, Physic :: Player {
	public:
		void draw();
	};
}

#endif