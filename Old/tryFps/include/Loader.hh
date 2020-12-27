#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif

#ifndef RV_ZD_COLLISION
#define RV_ZD_COLLISION
#include "Collision.hh"
#endif

#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif

#ifndef RV_ZD_VECTOR
#define RV_ZD_VECTOR
#include <vector>
#endif

#ifndef RV_ZD_MAP
#define RV_ZD_MAP
#include <map>
#endif

#ifndef RV_ZD_STRING
#define RV_ZD_STRING
#include <string>
#endif

#ifndef RV_ZD_FSTREAM
#define RV_ZD_FSTREAM
#include <fstream>
#endif

#ifndef RV_ZD_ALGORITHM
#define RV_ZD_ALGORITHM
#include <algorithm>
#endif






struct Face {
	int att_facenum;
	bool att_four;
	unsigned int att_faces[4];
	int att_texcoord[4];
	int att_mat;
	Face(int facen, unsigned int f1, unsigned int f2, unsigned int f3, int t1, int t2, int t3, int m);
	Face(int facen, unsigned int f1, unsigned int f2, unsigned int f3, unsigned int f4, int t1, int t2, int t3, int t4, int m);
};

struct Material {
	std::string att_name;
	float att_alpha, att_ns, att_ni;
	float att_dif[3], att_amb[3], att_spec[3];
	int att_illum;
	int att_texture;
	Material(const char* na, float al, float n, float ni2, float *d, float *a, float *s, int i, int t);
};

struct Texcoord {
	float att_u, att_v;
	Texcoord(float a,float b);
};

class Objloader {
	std :: vector <std :: string *> att_coord;
	std :: vector <Vector3f *> att_vertex;
	std :: vector <Face *> att_faces;
	std :: vector <Vector3f *> att_normals;
	std :: vector <unsigned int> att_texture;
	std :: vector <unsigned int> att_lists;
	std :: vector <Material *> att_materials;
	std :: vector <Texcoord *> att_textureCoordinate;
	std :: vector <Vector3f *> att_vertexNormals;
	bool att_isMaterial, att_isNormals, att_isTexture, att_isVertexNormal;

	std :: vector <std::string> att_loadedTextures;
	std :: vector <int> att_loadedTexturesNum;
	std :: ofstream att_out;
	
	unsigned int loadTexture(const char* filename);
	void clean();
	void smoothNormals();
public:
	Objloader();
	~Objloader();
	int load(const std :: string &filename, std :: vector <CollisionPlane> *collPlane);
};
