#include "PhE_CollisionSphere.hh"

Physic :: CollisionSphere &Physic :: CollisionSphere :: operator-=(const Vector3f &other) {
	att_center -= other;
	return *this;
}