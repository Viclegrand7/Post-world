#include "FPS_Ennemy.hh"

void FPS :: Ennemy :: draw() {
	att_graphEnnemy->draw(att_physEnnemy->givePos(), att_physEnnemy->giveRot());
}

void FPS :: Ennemy :: update(const Vector3f &character, const std :: vector<Physic :: Ennemy *> &ennemies, const std :: vector <Physic :: CollisionBox *> &wall, float gravity) {
	att_physEnnemy->update(character, ennemies, wall, gravity);
}
