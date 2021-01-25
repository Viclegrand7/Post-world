#ifndef RV_ZD_FPSENNEMY
#define RV_ZD_FPSENNEMY

#include "Ennemy.hh"
#include "PhE_Ennemy.hh"
#include "GrE_Ennemy.hh"

namespace FPS {
	class Ennemy {
	public:
		::Ennemy *att_gameEnnemy;
		Physic :: Ennemy *att_physEnnemy;
		Graphic :: Ennemy *att_graphEnnemy;
		
		void draw();
		void update(const Vector3f &character, const std :: vector<Physic :: Ennemy *> &ennemies, const std :: vector <Physic :: CollisionBox *> &wall, float gravity);
	};
}

#endif