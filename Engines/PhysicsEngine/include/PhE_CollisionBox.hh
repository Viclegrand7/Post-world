#ifndef RV_ZD_PHECOLLISIONBOX
#define RV_ZD_PHECOLLISIONBOX

#include "Vector3f.hh"
#include "PhE_CollisionQuad.hh"

namespace Physic {
	struct CollisionBox : public Obstacle { //Everything is public, let's gain some time
		CollisionQuad att_diagonals[2]; //I feel like you can get off with checking collision with 2 boxes only
		
		CollisionBox(const CollisionQuad &first, const CollisionQuad &second) : att_diagonals{first, second} {}
		CollisionBox(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3, const Vector3f &p4, const Vector3f &n1,
					 const Vector3f &p5, const Vector3f &p6, const Vector3f &p7, const Vector3f &p8, const Vector3f &n2)
		: att_diagonals{{p1, p2, p3, p4, n1}, {p5, p6, p7, p8, n2}} {}
		CollisionBox(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, 
			float x4, float y4, float z4, float xn1, float yn1, float zn1,
			float x5, float y5, float z5, float x6, float y6, float z6, float x7, float y7, float z7, 
			float x8, float y8, float z8, float xn2, float yn2, float zn2)
		: att_diagonals{{x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, xn1, yn1, zn1}, 
						{x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8, xn2, yn2, zn2}} {}
		CollisionBox &operator-=(const Vector3f &other) const {
			att_diagonals[0] -= other;
			att_diagonals[1] -= other;
		}
	};
}

#endif