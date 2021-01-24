#include "GrE_Board.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "GrE_Gun.hh"
#include "GrE_PowerUp.hh"

#define RV_ZD_GAMENAMEANDVERSION "Réaction Visible : Zone Dangereuse v1.0.0"

Graphic :: Board :: Board(const std :: string &fileName)  {
	if (SDL_Init(SDL_INIT_EVERYTHING)) { //Video, audio, handler, joysticks,... returns 0 on fail
		std :: cerr << "Failed initialising SDL: " << SDL_GetError() << std :: endl;
		throw "Failed initialising \n";
	}
	SDL_GetCurrentDisplayMode(0, &att_displayMode); //Asks computer for information considering the (current?) monitor
	att_fps = att_displayMode.refresh_rate;			//The monitor's display rate
	if (!(att_window = SDL_CreateWindow(RV_ZD_GAMENAMEANDVERSION, 0, 0, att_displayMode.w, att_displayMode.h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_OPENGL))) {
		std :: cerr << "Failed creating window: " << SDL_GetError() << std :: endl; //We created an info with a bunch of flags for what we needed, returns 0 on success
		throw "Failed creating window \n";
	}
	att_context = SDL_GL_CreateContext(att_window); //A way for us to draw with openGL on our window
	SDL_GL_SetSwapInterval(1); //Buffer swap synchronized with monitor's vertical refresh
	glClearColor(0.f, 0.f, 0.f, 1.0f); 	//We clear coloring black
	glMatrixMode(GL_PROJECTION);		//Further is smaller
	glLoadIdentity();					//You never know what used it last, always load identity
	gluPerspective(45.0f, 1.777778f, 0.1f, 400.0f); //Angle, width/height, how close you can see, how far
	glMatrixMode(GL_MODELVIEW);			//Honesly not sure what it does but you need it

	glEnable(GL_DEPTH_TEST);			//Things don't appear if they're behind non transparent walls
//	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);	//Requires to have normals on every shape, may be too much a bother
	glEnable(GL_LIGHT0); 	//Some lighting
	glEnable(GL_COLOR_MATERIAL); //Materials have colors too
	glEnable(GL_TEXTURE_2D);		//To attach textures to drawings


	std :: ifstream myFile(tryHardOpenFile(fileName)); 	//We are a loader, we can do that
	readAllFromFile(myFile);							//That function will load the ennemies, items,...
}

void Graphic :: Board :: readAllFromFile(std :: ifstream &myFile) {
//Here is what one of these files will look like: 
//	EnnemyFile		moveLength	attackLength	dieLength
//	MeleeNumber		WeaponFile	normLength	attackLength	secondaryLength	WeaponFile	...	secondaryLength
//	GunNumber		WeaponFile	normLength	attackLength	reloadLength	aimX aimY aimZ aimRotX aimRotY aimRotZ	WeaponFile	...	aimRotz
//	DefaultWeapon	PlayerFile
//	PowerUpNumber	PowerUpFile	PowerUpFile	...	PowerUpFile
//	ParticuleNumber	ParticuleFile	ParticuleDuration	ParticuleFile	...	ParticuleDuration	Level1
//	ParticuleNumber	ParticuleFile	ParticuleDuration	ParticuleFile	...	ParticuleDuration	Level2
//...
	std :: string nextFileToRead("");
	unsigned int length1(0), length2(0), length3(0), tmp(0);
	float tmpx(0.f), tmpy(0.f), tmpz(0.f), tmpRotx(0.f), tmpRoty(0.f), tmpRotz(0.f);
	std :: vector <Particule *> tmpParticules;
	myFile >> nextFileToRead >> length1 >> length2 >> length3;
	att_ennemies.emplace_back(new Ennemy(loadAnimation(nextFileToRead), length1, length2, length3));
	myFile >> att_weaponNumber;
	for (unsigned int i = 0 ; i < att_weaponNumber ; ++i) {
		myFile >> nextFileToRead >> length1 >> length2 >> length3;
		att_items.emplace_back(new Weapon(loadAnimation(nextFileToRead), length1, length2, length3));
	}
	myFile >> tmp;
	att_weaponNumber += tmp;
	for (unsigned int i = 0 ; i < tmp ; ++i) {
		myFile >> nextFileToRead >> length1 >> length2 >> length3 >> tmpx >> tmpy >> tmpz >> tmpRotx >> tmpRoty >> tmpRotz;
		att_items.emplace_back(new Gun(loadAnimation(nextFileToRead), Vector3f(tmpx, tmpy, tmpz), Vector3f(tmpRotx, tmpRoty, tmpRotz), length1, length2, length3));
	}
	myFile >> length1;
	for (unsigned int i = 0 ; i < length1 ; ++i) {
		myFile >> nextFileToRead;
		att_items.emplace_back(new PowerUp(loadAnimation(nextFileToRead)));
	}
	while (!myFile.eof()) {
		myFile >> length1;
		for (unsigned int i = 0 ; i < length1 ; ++i) {
			myFile >> nextFileToRead >> length2;
			att_particules.emplace_back(new Particule(loadFile(nextFileToRead), length2));
			tmpParticules.push_back(att_particules[att_particules.size() - 1]);
		}
		att_levels.emplace_back(new Level(loadAnimation(nextFileToRead), tmpParticules));
		tmpParticules.clear();
	}
}

void Graphic :: Board :: spawnEnnemy() {
	att_ennemies.emplace_back(new Ennemy(att_ennemies[0]));	//New ennemy. Position is in physics
}

void Graphic :: Board :: spawnItem(unsigned int id) {
	att_displayedItems.emplace_back(new Item(att_items[id])); //New item
}

void Graphic :: Board :: changeLevel(float spawnPitch, float spawnYaw, unsigned int levelNumber) {
	att_currentLevel = levelNumber;						//Changing level
	att_player->att_camera.lookAt(spawnPitch, spawnYaw);//Changing where the player looks
}

/*
void Graphic :: Board :: draw() { //This cannot work because we don't know positions of ennemies (PhysicsEngine), the weapon to draw(GameEngine),...
	float light_pos[] = {att_player->att_camera.giveLocation().att_x, att_player->att_camera.giveLocation().att_y + 2.f, att_player->att_camera.giveLocation().att_z, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);	//Modify Light0, positionning it where the player is (above him)
	float light_diff[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);	//White color
	float light_amb[] = {0.6f, 0.6f, 0.6f, 1.0f};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);	//Ambient light

	att_levels[att_currentLevel]->draw();
	for (unsigned int i = 0 ; i < att_ennemies ; ++i)
		att_ennemies[i]->draw(); //Position required
	for (unsigned int i = 0 ; i < att_displayedItems ; ++i)
		att_displayedItems[i]->draw(); //Position required
	
}
*/

void Graphic :: Board :: drawUI(int nbMags, int nbBullets, unsigned int HP) {
	glPushMatrix(); //Saves previous Matrix

	glLoadIdentity();							//To get the right position, independant of where we were
	glTranslatef(1.f, -1.f, -1.f); 	//Get to right position |||||||||||||||||||||-EXPERIMENTAL
	if (nbMags < 0) //Infinite bullets
		std :: cout << "Infinity" << std :: endl;
	else {
		std :: cout << nbMags << "  |  " << nbBullets << std :: endl;
	}
	std :: cout << HP << std :: endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glPopMatrix(); //Back to the saved Matrix
}

Graphic :: Board :: ~Board() {
	for (std :: map <std :: string, GLuint> :: iterator it = att_textures.begin() ; it != att_textures.end() ; ++it)
		glDeleteTextures(1, &it->second);
	for (unsigned int i = 0 ; i < att_drawings.size() ; ++i)
		glDeleteLists(att_drawings[i], 1);
	for (std :: map <std :: string, GLuint> :: iterator it = att_materials.begin() ; it != att_materials.end() ; ++it)
		glDeleteLists(it->second, 1);
	for (unsigned int i = 0 ; i < att_texVertex.size() ; ++i)
		delete[] att_texVertex[i];
	//We need to delete them here because we're the Loader, rather than possessing one

	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i)
		delete att_ennemies[i];
	for (unsigned int i = 0 ; i < att_items.size() ; ++i)
		delete att_items[i];
	for (unsigned int i = 0 ; i < att_displayedItems.size() ; ++i)
		delete att_displayedItems[i];
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i)
		delete att_levels[i];
	SDL_DestroyWindow(att_window);
	SDL_Quit();
	SDL_GL_DeleteContext(att_context);
}
