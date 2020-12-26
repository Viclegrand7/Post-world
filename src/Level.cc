#ifndef RV_ZD_LEVEL_H
#define RV_ZD_LEVEL_H
#include "Level.hh"
#endif

Level :: Level(const char *c, unsigned int mesh, std :: vector <CollisionPlane> &cp, std :: vector <Vector3f> &sp, 
	unsigned int left, unsigned int back, unsigned int right, unsigned int front, unsigned int roof, unsigned int floor, float size)
: att_mesh(mesh), att_colls(cp), att_spawnPoins(sp), att_name(c), att_map(new Map(left, back, right, front, roof, floor, size)) {}

void Level :: update() {

}
	
void Level :: display() {
	glCallList(att_mesh);
}

std :: vector<CollisionPlane> &Level :: getColl() {
	return att_colls;
}

std :: string &Level :: getName() {
	return att_name;
}

std :: vector <Vector3f> &Level :: getSpawn() {
	return att_spawnPoins;
}

void Level :: change(const char *c, unsigned int mesh, std :: vector <CollisionPlane> &cp, std :: vector <Vector3f> &sp) {
	att_mesh = mesh; 
	att_colls = cp;
	att_spawnPoins = sp;
	att_name = c;
}

Map *Level :: getMap() {
	return att_map;
}

Level :: ~Level() {
	delete att_map;
}