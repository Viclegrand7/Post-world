#include "PhE_Player.hh"


unsigned int Physic :: Player :: testCollisionItems(std :: vector <Item *> itemList) {
	for (unsigned int i = 0 ; i < itemList.size() ; ++i)
		if (Physic :: Collision :: doesSphereSphere(att_hitBox, itemList[i]->giveSphere()))
			return i;
	return itemList.size(); //Returns an error
}

void Physic :: Player :: testCollisionEnnemies(std :: vector <Ennemy *> ennemyList) {
	for (unsigned int i = 1 ; i < ennemyList.size() ; ++i) //First dude is the sample
		Physic :: Collision :: sphereSphere(att_hitBox, ennemyList[i]->giveSphere());
}

void Physic :: Player :: testCollisionWalls(std :: vector <CollisionQuad *> wallList) {
	for (unsigned int i = 0 ; i < wallList.size() ; ++i)
		Physic :: Collision :: sphereQuad(att_hitBox, *wallList[i]);
}

unsigned int Physic :: Player :: update(std :: vector <Item *> itemList, std :: vector <Ennemy *> ennemyList, std :: vector <CollisionQuad *> wallList) {
	testCollisionEnnemies(ennemyList);
	testCollisionWalls(wallList);
	return testCollisionItems(itemList); //Says which item we can interact with
}

void Physic :: Player :: setPos(const Vector3f &pos) {
	att_hitBox -= pos;
}
