#ifndef RV_ZD_PHECOLLISIONQUAD
#define RV_ZD_PHECOLLISIONQUAD

#include "Vector3f.hh"

namespace Physic {
	struct CollisionQuad : public Obstacle { //Everything is public, let's gain some time
		Vector3f att_corners[4]; //Consecutive order
		Vector3f att_normal; //Direction it's facing

		CollisionQuad(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3, const Vector3f &p4, const Vector3f &n)
		: att_corners{p1, p2, p3, p4}, att_normal(n) {}
		CollisionQuad(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, 
			float x4, float y4, float z4, float xn, float yn, float zn)
		: att_corners{{x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3}, {x4, y4, z4}}, att_normal({xn, yn, zn}) {}
		CollisionQuad operator-() const {return CollisionQuad(att_corners[0], att_corners[1], att_corners[2], att_corners[3], -att_normal);}
		CollisionQuad &operator-=(const Vector3f &other) const {
			for (unsigned int i = 0 ; i < 4 ; ++i)
				att_corners[i] -= other;
			att_normal -= other;
		}
	};
}

#endif