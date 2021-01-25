#ifndef RV_ZD_FPSPLAYER
#define RV_ZD_FPSPLAYER

#include "FPS_Camera.hh"
#include "GrE_Player.hh"
#include "PhE_Player.hh"
#include "Player.hh"
#include "vector"

namespace FPS {
	class Player {
	public:
		Graphic :: Weapon *att_knife;
		std :: vector <Graphic :: Weapon *> att_weapons;

		Graphic :: Player *att_graphPlayer;
		Physic :: Player *att_physPlayer;
		:: Player *att_gamePlayer;

		void draw();
		void attack();
		void secondary();
		void reload();

		void update(int width, int height, bool isFullScreen, float gravity);
	};
}

#endif