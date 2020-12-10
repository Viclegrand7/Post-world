#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif


CollisionPlane CollisionPlane :: operator-() const {
	return CollisionPlane(-att_normal, att_plane[0], att_plane[1], att_plane[2], att_plane[3]); //Facing opposite direction, normal is negative
}


bool Collision :: rayPlane(const CollisionPlane &plane, const Vector3f &origin, const Vector3f &direct, float* dis, Vector3f* point) {
	if (!plane.att_normal.dotProduct(direct)) //Dot product is 0, normal and direction are perpendicular, direction and plane are parallel
		return false;
	//We know the plane and direction may collide
	float dist((plane.att_plane[0] - origin).dotProduct(plane.att_normal));
	if (dist <= 0) {
		if (dis)
			*dis = 0;
		return false;
	}
	if (dis)
		*dis = dist;
	
	Vector3f collisionPoint(origin + direct * dist);
	if (point)
		*point = collisionPoint; //hitPoint. Now to check if it's on the rect
	//Divide in 2 triangles. If sum of 3sub-triangles (from collisionPoint) is equal to area of triangle, point is inside
	if (weirdTriangleArea(plane.att_plane[0], plane.att_plane[2], plane.att_plane[3]) - weirdTriangleArea(plane.att_plane[0], plane.att_plane[3], collisionPoint) - weirdTriangleArea(plane.att_plane[0], plane.att_plane[2], collisionPoint) - weirdTriangleArea(plane.att_plane[2], plane.att_plane[3], collisionPoint) && 
		weirdTriangleArea(plane.att_plane[0], plane.att_plane[1], plane.att_plane[2]) - weirdTriangleArea(plane.att_plane[0], plane.att_plane[1], collisionPoint) - weirdTriangleArea(plane.att_plane[0], plane.att_plane[2], collisionPoint) - weirdTriangleArea(plane.att_plane[1], plane.att_plane[2], collisionPoint) ) {
		if (dis)
			*dis = 0;
		if (point)
			*point = Vector3f(0,0,0);
		return false;
	}
	return true; //One of them was 0, meaning point was in one of the triangles
	//May need to make approximation using < 0.001f, then we'd need || instead of &&
}


float Collision :: weirdTriangleArea(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) { //Don't care much about sqrt, just want to compare areas
	float a = (p2.att_x - p1.att_x) * (p2.att_x - p1.att_x) + (p2.att_y - p1.att_y) * (p2.att_y - p1.att_y) + (p2.att_z - p1.att_z) * (p2.att_z - p1.att_z); //Should be sqrt'ed
	float b = (p3.att_x - p2.att_x) * (p3.att_x - p2.att_x) + (p3.att_y - p2.att_y) * (p3.att_y - p2.att_y) + (p3.att_z - p2.att_z) * (p3.att_z - p2.att_z); //Same
	float c = (p3.att_x - p1.att_x) * (p3.att_x - p1.att_x) + (p3.att_y - p1.att_y) * (p3.att_y - p1.att_y) + (p3.att_z - p1.att_z) * (p3.att_z - p1.att_z); //Same

	float s = (a + b + c)/2;
	return s * (s - a) * (s - b) * (s - c); //Same
}

bool Collision :: spherePlane(CollisionSphere &sphere, const CollisionPlane &plane) { //Bounces sphere back in case of running in wall
	float dist(0);
	//Quite proud of this one. If considering a ray starting from sphere center, going in opposite direction of the plane normal, we get the intersection if there is one
	if (rayPlane(plane, sphere.att_center, -plane.att_normal, &dist) && dist > sphere.att_radius) //There is a collision and the distance is too great
		return false;
	if (dist) { //Collision. Time to BOUNCE. Btw if sphere is in wall, we may bounce unexpectedly (considering big lag but sphere kept going in wall?)
		sphere.att_center += plane.att_normal * (sphere.att_radius - dist);
		return true;
	}

	//There was no collision, try again other direction
	if (rayPlane(-plane, sphere.att_center, plane.att_normal, &dist) && dist > sphere.att_radius) //Collision, distance too great
		return false;
	if (dist) { //We had a collision
		sphere.att_center -= plane.att_normal * (sphere.att_radius - dist);
		return true;
	}
	return false;
}

bool Collision :: raySphere(const Vector3f &origin, const Vector3f &direct, const CollisionSphere &sphere, float* dist, Vector3f* point) {
	float b(2 * (direct.dotProduct(sphere.att_center - origin)));
	float c((sphere.att_center - origin).dotProduct(sphere.att_center - origin) - sphere.att_radius * sphere.att_radius); //Basically we find the solution for collision saying the equation for sphere equals equation for ray
	float disc(b * b - 4 * c); //Direction normalized
	if (disc < 0) //Imaginary
		return false;
	if (dist)
		*dist = (-b + sqrt(disc)) / 2;
	if (point) {
		if (dist)
			*point = sphere.att_center + *dist * direct;
		else 
			*point = sphere.att_center + direct * (-b + sqrt(disc)) / 2;
	}
	return true;

}

bool Collision :: sphereSphere(CollisionSphere &sphere1, const CollisionSphere &sphere2) { //Sp1 gonna bounce back
	float dist((sphere1.att_center - sphere2.att_center).dotProduct(sphere1.att_center - sphere2.att_center));
	if (dist <= sphere1.att_radius * sphere2.att_radius) { //Colliding
		dist = sqrt(dist) - (sphere1.att_radius + sphere2.att_radius);
		Vector3f temp(sphere2.att_center - sphere1.att_center);
		temp.normalize();
		sphere1.att_center += dist * temp;
		return true;
	}
	return false;
}

float Collision :: pointDistance(const Vector3f &p1, const Vector3f &p2) {
	return sqrt((p2 - p1).dotProduct(p2 - p1));
}

//Maybe we should have weight for things to bounce in a smoother way, rather than sphere taking all (Although sphere is camera, and others are walls... uh.)