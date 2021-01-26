#ifndef RV_ZD_FPSBOARD
#define RV_ZD_FPSBOARD

#include "PhE_Board.hh"
#include "GrE_Board.hh"
#include "Ennemy.hh"
#include "FPS_Player.hh"

#include <vector>

namespace FPS {
	class Board {
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
	public:

		Board(const char *);
		~Board();

		void drawACube();
		void draw();
		void spawnEnnemy();
		void update();
		void run();
		void playerShoot(bool);
	};
}

#endif