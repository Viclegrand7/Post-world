#ifndef RV_ZD_PHECOLLISION
#define RV_ZD_PHECOLLISION

#include "Vector3f.hh"
#include "PhE_CollisionBox.hh"
#include "PhE_CollisionSphere.hh"
#include "PhE_CollisionQuad.hh"

namespace Physic {
	class Collision {
		//float att_weight;	//Future update, to know if things bounce back or what?

		static float weirdTriangleArea(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3); //To know if a point is in a triangle or not (useful for quads too)
	public:
		static bool rayPlane(const Vector3f &origin, const Vector3f &dir, const CollisionQuad &quad, float *distance = NULL, Vector3f *collisionPoint = NULL);
		static bool sphereQuad(CollisionSphere &someone, const CollisionQuad &quad); //Makes the someone bounce back from that wall
		static bool sphereBox(CollisionSphere &someone, const CollisionBox &quad); //Makes the someone bounce back from that box
		static bool raySphere(const Vector3f &origin, const Vector3f &dir, const CollisionSphere &sphere, float *distance = NULL, Vector3f *collisionPoint = NULL); //Do we hit?
		static bool sphereSphere(CollisionSphere &character, const CollisionSphere &someone); //Character will bounce back on others
		static bool doesSphereSphere(const CollisionSphere &character, const CollisionSphere &someone); //Can I reach that someone?
		static bool rayBox(const Vector3f &origin, const Vector3f &dir, const CollisionBox &box, float *distance = NULL, Vector3f *collisionPoint = NULL); //Hitting box? The collisionPoint will be inside, should not matter too much
	};
}

#endif