#include "PhE_CollisionBox.hh"

Physic :: CollisionBox &Physic :: CollisionBox :: operator-=(const Vector3f &other) {
	att_diagonals[0] -= other;
	att_diagonals[1] -= other;
	return *this;
}