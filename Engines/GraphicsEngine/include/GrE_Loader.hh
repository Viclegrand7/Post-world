#ifndef RV_ZD_GRELOADER
#define RV_ZD_GRELOADER

#include <GL/gl.h>
#include "Vector3f.hh"
#include <vector>
#include <string>
#include <map>

namespace Graphic {
	class Loader {
	protected:
		std :: map <std :: string, GLuint> att_textures; //Every .bmp file will be in there. The value is the corresponding texture
		std :: vector <GLuint> att_drawings; 	//Every list we have goes there 
		std :: map <std :: string, GLuint> att_materials; 	//Every material contains its informations (light, colors, alpha, texture,...)
		std :: vector <Vector3f> att_vertexes; 	//Every vertex in the obj (position)
		std :: vector <Vector3f> att_normals; 	//Every normal vertex in the obj (position)
		std :: vector <float *> att_texVertex;	//X and Y coordinates of the texture to use at a given point
		GLuint att_currentMaterial; 	//Useful to know which material to bind

		void loadTexture(const std :: string &file); 	//Load a .bmp file
		std :: ifstream tryHardOpenFile(const std :: string &file);
		void readVertex(const std :: string &vertexLine);
		void readNormal(const std :: string &vertexLine);
		void readMaterialLib(const std :: string &prevFileName, const std :: string &vertexLine);
		void readKs(const std :: string &VertexLine, float &Kx1, float &Kx2, float &Kx3);
		void readFloat(const std :: string &VertexLine, float &myVar, unsigned int numberOfCharToIgnore);
		void readInt(const std :: string &VertexLine, int &myVar);
		void readMaterial(const std :: string &path, std :: ifstream &myFile);
		void readTex(const std :: string &vertexLine);
		void readFigure(const std :: string &vertexLine);
	public:
		Loader() : att_textures(), att_drawings(), att_materials(), att_vertexes(), att_normals(), att_texVertex(), att_currentMaterial(0) {}
		GLuint loadFile(const std :: string &file);		//Load a .obj file. Returns the list to call to draw it all
		std :: vector <GLuint> loadAnimation(const std :: string &name); //Loads a whole animation for a given rootFileName (pistolet -> pistolet_abcdef.obj)
		~Loader();
	};

}

#endif