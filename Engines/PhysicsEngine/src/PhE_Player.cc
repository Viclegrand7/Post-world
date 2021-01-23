#include "PhE_Player.hh"


unsigned int Physic :: Player :: testCollisionItems(std :: vector <Item *> itemList) {
	for (unsigned int i = 0 ; i < itemList.size() ; ++i)
		if (doesSphereSphere(att_hitBox, itemList[i]->giveSphere()))
			return i;
	return itemList.size(); //Returns an error
}

void Physic :: Player :: testCollisionEnnemies(std :: vector <Ennemy *> ennemyList) {
	for (unsigned int i = 0 ; i < ennemyList.size() ; ++i)
		sphereSphere(att_hitBox, ennemyList[i]->giveSphere());
}

void Physic :: Player :: testCollisionWalls(std :: vector <CollisionBox *> wallList) {
	for (unsigned int i = 0 ; i < wallList.size() ; ++i)
		sphereBox(att_hitBox, wallList[i]);
}

void Physic :: Player :: attack(const vector3f &pos, const Vector3f &dir, std :: vector <Ennemy *> ennemyList, std :: vector <CollisionBox *> wallList) {
	float firstReachedWall(0); //Closest wall in our direction
	Vector3f posProjection{0.f, 0.f, 0.f};
	for (unsigned int i = 0 ; i < wallList.size() ; ++i)
		rayPlane(pos, dir, wallList[i]);
	for (unsigned int i = 0 ; i < ennemyList.size() ; ++i)

}

void Physic :: Player :: update(std :: vector <Item *> itemList, std :: vector <Ennemy *> ennemyList, std :: vector <CollisionBox *> wallList) {

}
