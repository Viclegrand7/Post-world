#include "PhE_Collision.hh"

#include <cmath>

float Physic :: Collision :: weirdTriangleArea(const Vector3f &p1, const Vector3f &p2, const Vector3f &p3) {
	float a = (p2.att_x - p1.att_x) * (p2.att_x - p1.att_x) + (p2.att_y - p1.att_y) * (p2.att_y - p1.att_y) + (p2.att_z - p1.att_z) * (p2.att_z - p1.att_z); //Should be sqrt'ed
	float b = (p3.att_x - p2.att_x) * (p3.att_x - p2.att_x) + (p3.att_y - p2.att_y) * (p3.att_y - p2.att_y) + (p3.att_z - p2.att_z) * (p3.att_z - p2.att_z); //Same
	float c = (p3.att_x - p1.att_x) * (p3.att_x - p1.att_x) + (p3.att_y - p1.att_y) * (p3.att_y - p1.att_y) + (p3.att_z - p1.att_z) * (p3.att_z - p1.att_z); //Same

	float s = (a + b + c)/2;
	return s * (s - a) * (s - b) * (s - c); //Same
}

bool Physic :: Collision :: rayPlane(const Vector3f &origin, const Vector3f &dir, const CollisionQuad &quad, float *distance, Vector3f *collisionPoint) {
	if (!quad.att_normal.dotProduct(dir)) //Dot product is 0, normal and direction are perpendicular, direction and quad are parallel
		return false;
	//We know the quad and direction may collide
	float dist((quad.att_corners[0] - origin).dotProduct(quad.att_normal));
	if (dist <= 0) //Collision is behind us
		return false;
	Vector3f cPoint(origin + dir * dist);

	//Divide in 2 triangles. If sum of 3sub-triangles (from cPoint) is equal to area of triangle, point is inside
	if (weirdTriangleArea(quad.att_corners[0], quad.att_corners[2], quad.att_corners[3]) - weirdTriangleArea(quad.att_corners[0], quad.att_corners[3], cPoint) - weirdTriangleArea(quad.att_corners[0], quad.att_corners[2], cPoint) - weirdTriangleArea(quad.att_corners[2], quad.att_corners[3], cPoint) > 0.001f &&
		weirdTriangleArea(quad.att_corners[0], quad.att_corners[1], quad.att_corners[2]) - weirdTriangleArea(quad.att_corners[0], quad.att_corners[1], cPoint) - weirdTriangleArea(quad.att_corners[0], quad.att_corners[2], cPoint) - weirdTriangleArea(quad.att_corners[1], quad.att_corners[2], cPoint) > 0.001f)
		return false;
	if (distance && (*distance > dist || !*distance)) {//We found a wall closer than the ones found before
		*distance = dist;
		if (collisionPoint)
			*collisionPoint = cPoint;
	}
	return true; //One of them was 0, meaning point was in one of the triangles
}

bool Physic :: Collision :: sphereQuad(CollisionSphere &someone, const CollisionQuad &quad) {
	float dist(0);
	//Quite proud of this one. If considering a ray starting from sphere center, going in opposite direction of the plane normal, we get the intersection if there is one
	if (rayPlane(someone.att_center, -quad.att_normal, quad, &dist) && dist > someone.att_radius) //There is a collision and the distance is too great
		return false;
	if (dist) { //Collision. Time to BOUNCE. Btw if sphere is in wall, we may bounce unexpectedly (considering big lag but sphere kept going in wall?)
		someone.att_center += quad.att_normal * (someone.att_radius - dist);
		return true;
	}

	//There was no collision, try again other direction
	if (rayPlane(someone.att_center, quad.att_normal, -quad, &dist) && dist > someone.att_radius) //Collision, distance too great
		return false;
	if (dist) { //We had a collision
		someone.att_center -= quad.att_normal * (someone.att_radius - dist);
		return true;
	}
	return false;
}

bool Physic :: Collision :: sphereBox(CollisionSphere &someone, const CollisionBox &box) {
	bool tmp(sphereQuad(someone, box.att_diagonals[0]));
	bool tmp2(sphereQuad(someone, box.att_diagonals[1]));
	return (tmp || tmp2);
}

bool Physic :: Collision :: raySphere(const Vector3f &origin, const Vector3f &dir, const CollisionSphere &sphere, float *distance, Vector3f *collisionPoint) {
	float b(2 * (dir.dotProduct(sphere.att_center - origin)));
	float c((sphere.att_center - origin).dotProduct(sphere.att_center - origin) - sphere.att_radius * sphere.att_radius); //Basically we find the solution for collision saying the equation for sphere equals equation for ray
	float discrim(b * b - 4 * c); //Direction normalized
	if (discrim < 0) //Imaginary
		return false;
	float dist((- b + sqrt(discrim)) / 2);
	if (distance && *distance < dist) //A wall is between us and target
		return false; 
	if (collisionPoint) //Need to provide an info concerning where we hit him
		*collisionPoint = sphere.att_center + dist * dir;
	return true;
}

bool Physic :: Collision :: sphereSphere(CollisionSphere &character, const CollisionSphere &someone) {
	float dist((character.att_center - someone.att_center).dotProduct(character.att_center - someone.att_center));
	if (dist <= character.att_radius * someone.att_radius) { //Colliding
		dist = sqrt(dist) - (character.att_radius + someone.att_radius);
		Vector3f temp(someone.att_center - character.att_center);
		temp.normalize();
		character.att_center += dist * temp;
		return true;
	}
	return false;
}

bool Physic :: Collision :: doesSphereSphere(const CollisionSphere &character, const CollisionSphere &someone) {
	float dist((character.att_center - someone.att_center).dotProduct(character.att_center - someone.att_center));
	if (dist <= character.att_radius * (someone.att_radius)) { //Colliding
		return true;
	}
	return false;
}

bool Physic :: Collision :: rayBox(const Vector3f &origin, const Vector3f &dir, const CollisionBox &box, float *distance, Vector3f *collisionPoint) {
	bool tmp(rayPlane(origin, dir, box.att_diagonals[0], distance, collisionPoint));
	bool tmp2(rayPlane(origin, dir, box.att_diagonals[1], distance, collisionPoint));
	return (tmp || tmp2); //Probably could be return (whatIsInTmp2 || tmp1) but I fear it would not always take the 'closest' (although it probably does not already)
}
