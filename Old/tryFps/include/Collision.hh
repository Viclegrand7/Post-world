#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif
//Gonna be using Vector3f


struct CollisionSphere {
	float att_radius;
	Vector3f att_center;
	CollisionSphere(Vector3f center, float radius = 0) : att_radius(radius), att_center(center) {}
};


struct CollisionPlane {
	Vector3f att_plane[4]; 	//4 points in space
	Vector3f att_normal;	//Normal plane
	CollisionPlane(const Vector3f &normal, const Vector3f &p1, const Vector3f &p2, const Vector3f &p3, const Vector3f &p4) : att_plane{p1, p2, p3, p4}, att_normal(normal) {}
	CollisionPlane operator-() const;
};

struct Collision {
	static bool rayPlane(const CollisionPlane &plane, const Vector3f &origin, const Vector3f &direct, float* dis=NULL, Vector3f* point=NULL);
	static float weirdTriangleArea(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3); //Square of area
	static bool spherePlane(CollisionSphere &sphere, const CollisionPlane &plane); //Sphere bouncing back baby
	static bool raySphere(const Vector3f &origin, const Vector3f &direct, const CollisionSphere &sphere, float* dist=NULL, Vector3f* point=NULL);
	static bool sphereSphere(CollisionSphere &sphere1, const CollisionSphere &sphere2);
	static float pointDistance(const Vector3f &p1, const Vector3f &p2);
};