#include "PhE_Item.hh"

const Physic :: CollisionSphere &Physic :: Item :: giveSphere() const {
	return att_hitBox;
}