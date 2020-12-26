#ifndef RV_ZD_GAME_H
#define RV_ZD_GAME_H
#include "Game.hh"
#endif



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	SDL_Texture *background = window.loadTexture("../res/img/Background.png");
	entities.push_back(Entity(Vector3f(0,0,0), background));
*/
/*
	{
		Entity platform0(Vector3f(100, 0, 0), imaginaryTexture);
		entities.push_back(platform0);
	} //Adding those create a scope, ensuring platform0 gets deleted afterwards. Same than entities.pushback(Entity(Vector3f(100, 0, 0), imaginaryTexture))?
*/
/*
		att_render.clear();
		for (Entity &someone : entities)
			att_render.render(someone);
//		att_render.render(platform0);
		att_render.display();

*/
/*
	entities.clear();
	{
		SDL_Texture *background = att_render.loadTexture("../res/img/Background.png");
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
		entities.push_back(Entity(Vector3f(0.0f, 0.0f, 0.0f), background));
	}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int skybox[6];

unsigned int Game :: loadTexture(const char* filename)	//load the filename named texture
{

	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* img=SDL_LoadBMP(filename);	//load the bmp image
	glBindTexture(GL_TEXTURE_2D,num);	//and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	return num;	//and we return the id


/*
	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* tmp(IMG_Load(filename));	//load the png image
	SDL_Surface* img(SDL_ConvertSurface(tmp, format, 0));	//Optimize the png
	SDL_FreeSurface(tmp);
	glBindTexture(GL_TEXTURE_2D,num);	//and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D,	0,GL_RGB,	img->w,img->h,0,	GL_RGB,GL_UNSIGNED_SHORT_5_6_5,	img->pixels);	//we make the actual texture
	SDL_FreeSurface(img);	//we delete the image, we don't need it anymore
	return num;	//and we return the id
*/
}

/*
	int size = 50;

	glDisable(GL_LIGHTING);	//turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,skybox[0]);	//use the texture we want
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glTexCoord2f(0,0);	//use the correct texture vector3d
		glVertex3f(size/2,size/2,size/2);	//and a vertex
		glTexCoord2f(1,0);	//and repeat it...
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,size/2);
	glEnd();

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










Game :: Game(SDL_DisplayMode DM) : att_render("Best_Game v0.0", DM.w, DM.h) {
	att_fps = DM.refresh_rate;


	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, 1.777778f, 1.0f, 500.0f); //Angle, width/height, how close you can see, how far
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

	std :: vector <CollisionPlane> tmp_cp;
	std :: vector <Vector3f> tmp_sp;
	tmp_sp.push_back(Vector3f(3.0f, 4.0f, 5.0f)); //Ennemies spawns
	unsigned int lvl = att_obj.load("../res/obj/map/map.obj", &tmp_cp);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned int left(loadTexture("../res/img/left.bmp"));
	unsigned int back(loadTexture("../res/img/back.bmp"));
	unsigned int right(loadTexture("../res/img/right.bmp"));
	unsigned int front(loadTexture("../res/img/front.bmp"));
	unsigned int roof(loadTexture("../res/img/top.bmp"));
	unsigned int floor(loadTexture("../res/img/bottom.bmp"));

	att_levels.emplace_back(new Level("name", lvl, tmp_cp, tmp_sp, back, left, front, right, roof, floor, 500));

	std :: vector <unsigned int> anim;
	loadAnimation(anim, "../res/obj/weapons/chair-back_column3", 1); //Default weapon = Puck (don't ask)
	//Last number = number of frames (total)

	att_weapons.emplace_back(new Weapon(anim, anim[0], 1, 0, 0, false, Vector3f(0.5f, -0.5f, -1.5f), Vector3f(0.0f, -80.0f, 0.0f), 
		Vector3f(-0.25f, -0.75f, -1.75f), Vector3f(0.0f, -90.0f, 0.0f),	90, 100, 10, 8, 120, 10, "Puck"));
/*
	Reminder:
	Weapon(std :: vector <unsigned int> &animation, unsigned int look, unsigned int normal, unsigned int fire, unsigned int reload, bool isAuto, Vector3f pos, 
		Vector3f rot, Vector3f aimPos, Vector3f aimRot, float prec, float aimPrec, unsigned int dmg, unsigned int maxB, unsigned int allB, unsigned int speed, std :: string &name);
*/


//	anim.clear();
//	loadAnimation(anim, "../res/obj/ennemy", 60);
//	att_ennemies.emplace_back(new Ennemy(anim, 30, 20, 10, 40, 30, 0.1, CollisionSphere(Vector3f(5.0f, 10.0f, 0.0f), 1.5)));
/*
	Reminder:
	Ennemy(const std :: vector <unsigned int> &anim, unsigned int walk, unsigned int attack, unsigned int death, int health, int damage, float speed, const CollisionSphere &cs);
*/

	Vector3f tmp_pos(10.0f, 10.0f, 10.0f);
	att_player = new Player("User", CollisionSphere(tmp_pos, 1.5f), att_weapons[0]);
}

Game :: ~Game() {
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i)
		delete att_levels[i];
	for (unsigned int i = 0 ; i < att_weapons.size() ; ++i)
		delete att_weapons[i];
	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i)
		delete att_ennemies[i];
	att_render.cleanUp();
	SDL_Quit();
}

void Game :: run() {

//	SDL_Texture *imaginaryTexture = window.loadTexture("../res/img/someImage.png");

/*
	SDL_Texture *background = window.loadTexture("../res/img/Background.png");
	entities.push_back(Entity(Vector3f(0,0,0), background));
*/
/*
	{
		Entity platform0(Vector3f(100, 0, 0), imaginaryTexture);
		entities.push_back(platform0);
	} //Adding those create a scope, ensuring platform0 gets deleted afterwards. Same than entities.pushback(Entity(Vector3f(100, 0, 0), imaginaryTexture))?
*/


	bool isRunning = true;
	Uint32 currentTimeTick(0); //FPS regulation

	SDL_Event event;

	Vector3f dir;
	bool LMB_down(false);

	while (isRunning) {
		currentTimeTick = SDL_GetTicks();
	
		while (SDL_PollEvent(&event))
			switch (event.type) {
				case SDL_QUIT :
					isRunning = false;
				break;
				case SDL_MOUSEWHEEL:
					if (event.wheel.y > 0) {
						att_player->nextWeapon();
					}
					if (event.wheel.y < 0) {
						att_player->prevWeapon();
					}
				break;
				case SDL_MOUSEBUTTONDOWN :
					if (event.button.button == SDL_BUTTON_LEFT && att_player->att_cam.isMouseIn()) {
						LMB_down = true;
					}
					else if (event.button.button == SDL_BUTTON_RIGHT && att_player->att_cam.isMouseIn())
						att_player->getCurWeapon()->aim();
					att_player->att_cam.mouseIn(true);
//					if (inOptions) {
//						//Do stuff
//					}
//					else
//						SDL_ShowCursor(SDL_ENABLE);
						SDL_ShowCursor(SDL_DISABLE);
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_1:
							att_player->changeWeapon(0);
						break;
						case SDL_SCANCODE_2:
							att_player->changeWeapon(1);
						break;
						case SDL_SCANCODE_3:
							att_player->changeWeapon(2);
						break;
						case SDL_SCANCODE_R:
							att_player->getCurWeapon()->reload();
						break;
						case SDL_SCANCODE_SPACE:
							att_player->jump();
						break;
						case SDL_SCANCODE_LSHIFT:
							att_player->sprint();
						break;
						default:
						break;
					}
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
						att_player->noSprint();
				break;
				case SDL_MOUSEBUTTONUP: {
					if (event.button.button == SDL_BUTTON_LEFT) {
						att_player->getCurWeapon()->stopFire();
						LMB_down = false;
					}
				}
				break;
// 				case SDL_MOUSEMOTION:
// //					if (inOptions) {
// //						//Do stuff
// //					}
// 					att_cam.control(att_render);
// 				break;
			}

		if (LMB_down) {
			if (att_player->getCurWeapon()->fire(dir, att_player->att_cam.getVec())) //If we can shoot
				for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i) {
					if (Collision :: raySphere(att_player->att_cam.getLoc(), att_player->att_cam.getVec(), att_ennemies[i]->getCollSphere()))
						att_ennemies[i]->getHit(att_player->getCurWeapon()->getDmg());
//Atm we hit every single ennemy, even through walls

			}
		}

		update();
		display();



/*
		att_render.clear();
		for (Entity &someone : entities)
			att_render.render(someone);
//		att_render.render(platform0);
		att_render.display();
*/

		SDL_GL_SwapWindow(att_render.getWindow());

		if (1000./att_fps > SDL_GetTicks() - currentTimeTick)
			SDL_Delay(1000./att_fps - (SDL_GetTicks() - currentTimeTick)); //FPS regulation based on how fast monitor can go

	}

}

void Game :: update() {
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i) 
		att_levels[i]->update();
	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i) {
		if (att_ennemies[i]->update(att_levels[0]->getColl(), att_player->getSphere().att_center)) {//Died
			att_items.add(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), att_ennemies[i]->getCollSphere(), 0, att_weapons[1]->getLook()); //He drops weapon n°1 everytime
			delete att_ennemies[i];
			att_ennemies.erase(att_ennemies.begin() + i--); //We get to prev, delete next, let the for go to next
		}
		else if (att_ennemies[i]->setAttack(att_player->getSphere())) { //Attacking player
			att_player->addHealth(- att_ennemies[i]->getDamage());
		}
	}
	int tmp(att_items.update(att_player->getSphere()));
	if (tmp != -1)
		att_player->addWeapon(att_weapons[tmp]); //Change so it is an actual swap
	att_player->update(att_levels[0]->getColl());
}


void Game :: display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	att_render.isFull() ? att_player->att_cam.control(att_render, true) : att_player->att_cam.control(att_render, false);
	att_levels[0]->getMap()->drawMap();
	att_player->att_cam.updateCamera();
	for (unsigned int i = 0 ; i < att_levels.size() ; ++i) //Probably should just display and update the level we're in
		att_levels[i]->display();
	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i) //Deal with distance to know if auto death?
		att_ennemies[i]->display();
	att_items.display();
	att_player->display();
}

void Game :: loadAnimation(std :: vector <unsigned int> &anim, const std :: string &filename, int frames) {
	std :: string tmp("");
	for (int i = 0 ; i < frames ;) {
		if (i++ < 10)
			tmp = "_00000" + std :: to_string(i);
		else if (i < 100)
			tmp = "_0000" + std :: to_string(i);
		else if (i < 1000)
			tmp = "_000" + std :: to_string(i);
		else if (i < 10000)
			tmp = "_00" + std :: to_string(i);
		else if (i < 100000)
			tmp = "_0" + std :: to_string(i);
		else if (i < 1000000)
			tmp = "_" + std :: to_string(i);
		tmp = filename + tmp + ".obj";
		anim.push_back(att_obj.load(tmp, NULL)); //Need to add a way to load animations
	}
}