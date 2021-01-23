#include "PhE_CollisionQuad.hh"

Physic :: CollisionQuad &Physic :: CollisionQuad :: operator-=(const Vector3f &other) {
	for (unsigned int i = 0 ; i < 4 ; ++i)
		att_corners[i] -= other;
	att_normal -= other;
	return *this;
}