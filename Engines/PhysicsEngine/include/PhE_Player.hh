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
		Player(const CollisionSphere &sphere = CollisionSphere({0.f, 0.f, 0.f}, 2.f)) : att_hitBox(sphere) {}
		Vector3f &givePos() {return att_hitBox.att_center;}
		void setPos(const Vector3f &pos);
		unsigned int update(std :: vector <Item *> itemList, std :: vector <Ennemy *> ennemyList, std :: vector <CollisionBox *> wallList);
	};
}

#endif