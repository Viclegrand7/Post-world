#ifndef RV_ZD_PHEPBOARD
#define RV_ZD_PHEBOARD

#include "PhE_Item.hh"
#include "PhE_Player.hh"
#include "PhE_CollisionBox.hh"
#include "PhE_CollisionQuad.hh"
#include "PhE_Collision.hh"
#include "PhE_Ennemy.hh"
#include "Vector3f.hh"

#include <vector>

namespace Physic {
	class Board {
		std :: vector <Vector3f> att_vertexes; 	//Every vertex in the obj (position)
		std :: vector <Vector3f> att_normals; 	//Every normal vertex in the obj (position)
		int att_currentMaterial;
		bool att_currentSecond[6];
		Physic :: CollisionQuad att_tmpQuads[6];

		std :: ifstream tryHardOpenFile(const std :: string &file);
		void readVertex(const std :: string &vertexLine);
		void readNormal(const std :: string &vertexLine);
		void readFigure(const std :: string &vertexLine, Physic :: Ennemy &myEnnemy);
		Physic :: Ennemy loadFile(const std :: string &file);		//Load a .obj file
		void loadAnimation(const std :: string &name);
		void loadLevel(const std :: string &name, unsigned int number);
		void loadFigure(const std :: string &name, unsigned int number);
		Physic :: CollisionSphere loadSphere(const std :: string &line);
		void loadPowerUp(const std :: string &name);
	public:
		unsigned int att_curLevel;
		std :: vector <Ennemy *> att_ennemies;
		std :: vector <Item *> att_items;
		std :: vector <std :: vector <CollisionQuad *>> att_levels;
		void changeLevel(unsigned int level);		
//		std :: vector<Vector3f> playerShoot(const Vector3f &dir);
		Board(const char* filename);
		~Board();
	};
}

#endif
