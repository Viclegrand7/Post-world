#ifndef RV_ZD_PHECOLLISIONSPHERE
#define RV_ZD_PHECOLLISIONSPHERE

#include "Vector3f.hh"

namespace Physic {
	struct CollisionSphere : public Obstacle { //Everything is public, let's gain some time
		Vector3f att_center;
		float att_radius; //How big

		CollisionSphere(const Vector3f &cen, float rad) : att_center(cen), att_radius(rad) {}
		CollisionSphere(float x, float y, float z, float rad) : att_center({x, y, z}), att_radius(rad) {}
		CollisionSphere &operator-=(const Vector3f &other) const {att_center -= other;}
	};
}

#endif