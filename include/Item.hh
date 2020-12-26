#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif

#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif

#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif

#ifndef RV_ZD_GLU_H
#define RV_ZD_GLU_H
#include <GL/glu.h>
#endif




struct Item {
	Vector3f att_rotation, att_scale;
	CollisionSphere att_collSphere;
	int att_id;
	unsigned int att_texture;
	Item(const Vector3f &rotation, const Vector3f &scale, const CollisionSphere &cs, int id, int texture);
};

class Inventory {
	std :: vector <Item> att_items;
public:
	void add(const Vector3f &rotation, const Vector3f &scale, const CollisionSphere &cs, int id, int texture);
	void del(int id);
	int update(const CollisionSphere &playerPos);
	void display();
};