#ifndef RV_ZD_FPSBOARD
#define RV_ZD_FPSBOARD

#include "PhE_Board.hh"
#include "GrE_Board.hh"
#include "FPS_Ennemy.hh"
#include "FPS_Player.hh"
#include "FPS_Item.hh"
#include "FPS_Weapon.hh"

#include <vector>

namespace FPS {
	class Board {
	public:
		Physic :: Board *att_physBoard;
		Graphic :: Board *att_graphBoard;

		std :: vector <::Ennemy *> att_gameEnnemies;
		std :: vector <::Item *> att_gameItems;
		std :: vector <::Item *> att_displayedGameItems;
		std :: vector <::Weapon *> att_gameWeapons;
		Player *att_player;
		unsigned int att_timeBeforeSpawn;
		unsigned int att_numberToSpawn;
		unsigned int att_timeSinceLastSpawn;

		Board(const char *);
		~Board();

		void draw();
		void spawnEnnemy();
		void update();
		void run();
		void playerShoot(bool);
	};
}

#endif