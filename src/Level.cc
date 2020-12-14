#ifndef RV_ZD_LEVEL_H
#define RV_ZD_LEVEL_H
#include "Level.hh"
#endif

Level :: Level(const char *c, unsigned int mesh, std :: vector <CollisionPlane> &cp, std :: vector <Vector3f> &sp) 
: att_mesh(mesh), att_colls(cp), att_spawnPoins(sp), att_name(c) {}

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
	
Level :: ~Level() {}