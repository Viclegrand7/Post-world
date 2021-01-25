#ifndef RV_ZD_GREBOARD
#define RV_ZD_GREBOARD

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "GrE_Ennemy.hh"
#include "GrE_Loader.hh"
#include "GrE_Item.hh"
#include "GrE_Player.hh"
#include "GrE_Level.hh"
#include "GrE_Particule.hh"

namespace Graphic {
	class Board : public Loader { //So he is a loader, so he knows the textures, drawings, without needing useless getters
	protected:
		float att_gravity;							//How much gravity there is
		unsigned int att_weaponNumber;				//Number of available weapons
		SDL_DisplayMode att_displayMode;			//FPS information, monitor one,...
		SDL_GLContext att_context;					//Some context related to our window to draw on it

		//Ideally we would have more ennemy templates, so we would need another vector for the ennemiesAlive
		std :: vector <Particule *> att_particules;	//Available particules

		void readAllFromFile(std :: ifstream &myFile); 	//So we send it one file that will say where to look and everything
	public:
		int att_fps;								//FPS regulation
		SDL_Window *att_window;						//Our window
		unsigned int att_currentLevel;				//Self explanatory
		Board(const std :: string &fileName);
		std :: vector <Item *> att_items;			//All the existing items that can be created
		std :: vector <Level *> att_levels;			//The different maps
		std :: vector <Ennemy *> att_ennemies; 		//A way to make ennemies, and the list of living. We don't use number 0, he is a "template"
		std :: vector <Item *> att_displayedItems;	//All the items currently existing
		void draw(const Vector3f &);
//		void update(); //Honestly can't do it here. It checks if ennemies die, if items are used,... Those information interest gameEngine
		//They also require information like if they attack, die, get used,...
		void spawnEnnemy();
		void spawnItem(unsigned int id);
		void changeLevel(unsigned int levelNumber);
		void drawUI(int nbMags, int nbBullets, unsigned int HP);
		float getGravity() {return att_gravity;}
		virtual ~Board();
	};
}

#endif