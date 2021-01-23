#ifndef RV_ZD_PHEPBOARD
#define RV_ZD_PHEBOARD

#include "PhE_Item.hh"
#include "PhE_Player.hh"
#include "PhE_CollisionBox.hh"
#include "PhE_Collision.hh"
#include "PhE_Ennemy.hh"
#include "Vector3f.hh"

#include <vector>

namespace Physic {
	class Board {
		Player *att_player;
		std :: vector <Ennemy *> att_ennemies;
		std :: vector <Item *> att_items;
		std :: vector <std :: vector <CollisionBox *>> att_levels;
		unsigned int att_curLevel;
	public:
		std :: vector<Vector3f> playerShoot(const Vector3f &dir);
		void changeLevel(const Vector3f &spawnPosition, unsigned int level);
	};
}

#endif
