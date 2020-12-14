#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif

#ifndef RV_ZD_IOSTREAM
#define RV_ZD_IOSTREAM
#include <iostream>
#endif

#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_STRING
#define RV_ZD_STRING
#include <string>
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif




class Level {
	unsigned int att_mesh;
	std :: vector <CollisionPlane> att_colls;
	std :: vector <Vector3f> att_spawnPoins;
	std :: string att_name;
public:
	Level(const char *c, unsigned int mesh, std :: vector <CollisionPlane> &cp, std :: vector <Vector3f> &sp);
	void update();
	void display();

	std :: vector<CollisionPlane> &getColl();
	std :: string &getName();
	std :: vector <Vector3f> &getSpawn();
	void change(const char *c, unsigned int map, std :: vector <CollisionPlane> &cplane, std :: vector <Vector3f> &sp);
	
	~Level();
};