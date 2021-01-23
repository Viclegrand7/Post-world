#ifndef RV_ZD_PHEPLAYER
#define RV_ZD_PHEPLAYER

#include "PhE_Item.hh"
#include "PhE_Ennemy.hh"
#include "Vector3f.hh"

#include <vector>

namespace Physic {
	class Player {
		CollisionSphere att_hitBox;

		unsigned int testCollisionItems(std :: vector <Item *> itemList); //Returns the first element we collide with in the list
		void testCollisionEnnemies(std :: vector <Ennemy *> ennemyList); //Physics, bump into them
		void testCollisionWalls(std :: vector <CollisionBox *> wallList); //Physics, bump into them
	public:
		Player(const CollisionSphere &sphere) : att_hitBox(sphere) {}
		void attack(const Vector3f &pos, const Vector3f &dir, std :: vector <Ennemy *> ennemyList, std :: vector <Obstacle *> wallList);
		void update(std :: vector <Item *> itemList, std :: vector <Ennemy *> ennemyList, std :: vector <Obstacle *> wallList);
	};
}

#endif