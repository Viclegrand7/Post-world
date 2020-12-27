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

#ifndef RV_ZD_MAP_H
#define RV_ZD_MAP_H
#include "Map.hh"
#endif




class Level {
	unsigned int att_mesh;
	std :: vector <CollisionPlane> att_colls;
	std :: vector <Vector3f> att_spawnPoins;
	std :: string att_name;
	Map *att_map;
public:
	Level(const char *c, unsigned int mesh, std :: vector <CollisionPlane> &cp, std :: vector <Vector3f> &sp, 
		unsigned int left, unsigned int back, unsigned int right, unsigned int front, unsigned int roof, unsigned int floor, float size);
	void update();
	void display();

	std :: vector<CollisionPlane> &getColl();
	std :: string &getName();
	std :: vector <Vector3f> &getSpawn();
	void change(const char *c, unsigned int map, std :: vector <CollisionPlane> &cplane, std :: vector <Vector3f> &sp);
	Map *getMap();
	
	~Level();
};