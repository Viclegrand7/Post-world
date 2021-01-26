#include "FPS_Board.hh"
#include "PhE_Collision.hh"

#include <iostream>
#include <GL/gl.h>

FPS :: Board :: Board(const char *filename) : att_physBoard(NULL), att_graphBoard(NULL), att_gameEnnemies{}, att_gameItems{}, att_displayedGameItems{}, att_gameWeapons{}, att_player(NULL), att_timeBeforeSpawn(120), att_numberToSpawn(0), att_timeSinceLastSpawn(200) {
	att_graphBoard = new Graphic :: Board(filename); //He read everything, started the window,filled its attributes,...
	att_physBoard = new Physic :: Board(filename); //Took care of collisionBoxes
	att_gameEnnemies.push_back(new ::Ennemy());
//	att_gameItems.emplace_back(new Game :: PowerUp(std :: string name, int id));
//	att_gameWeapons.emplace_back(new Game :: Melee(int damage, int attackDownTime, float range, int secondaryDownTime))
	att_gameWeapons.emplace_back(new ::Melee(100, 10, 3.f, 20));
//	att_gameWeapons.emplace_back(new Game ::Gun(int damage, bool isAuto, int attackDownTime, int maxMagazine, int maxBullet, float precision));
	att_gameWeapons.emplace_back(new ::Gun(20, false, 6, 14, 200, 1));
	att_gameWeapons.emplace_back(new ::Gun(100, false, 25, 5, 50, 1));
	std :: vector <Graphic :: Weapon *> playerWeapon;
	playerWeapon.push_back((Graphic :: Weapon *)att_graphBoard->att_items[1]);
	std :: vector <:: Weapon *> playerPWeapon;
	playerPWeapon.push_back(att_gameWeapons[1]);
	att_player = new Player((Graphic :: Weapon *)att_graphBoard->att_items[0], playerWeapon, (::Melee *)att_gameWeapons[1], playerPWeapon);
	att_player->att_gamePlayer->getCurrentWeapon() = 1;
}

FPS :: Board :: ~Board() {
	// for (unsigned int i = 0 ; i < att_physBoard->att_ennemies.size() ; ++i)
	// 	delete att_physBoard->att_ennemies[i];
	// for (unsigned int i = 0 ; i < att_graphBoard->att_ennemies.size() ; ++i)
	// 	delete att_graphBoard->att_ennemies[i];
	// for (unsigned int i = 0 ; i < att_gameEnnemies.size() ; ++i)
	// 	delete att_gameEnnemies[i];
		delete att_gameEnnemies[0];
		delete att_graphBoard->att_ennemies[0];
		delete att_physBoard->att_ennemies[0];
	for (unsigned int i = 0 ; i < att_gameItems.size() ; ++i)
		delete att_gameItems[i];
	for (unsigned int i = 0 ; i < att_gameWeapons.size() ; ++i)
		delete att_gameWeapons[i];
	delete att_graphBoard;
	delete att_physBoard;
	delete att_player;
}

void FPS :: Board :: drawACube() {
	glColor3f(1,1,1);
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glColor3f(0,1,1);
		glVertex3f(200.f/2,200.f/2,200.f/2);	//and a vertex
		glColor3f(1,0,1);
		glVertex3f(-200.f/2,200.f/2,200.f/2);
		glColor3f(1,1,0);
		glVertex3f(-200.f/2,-200.f/2,200.f/2);
		glColor3f(1,0,0);
		glVertex3f(200.f/2,-200.f/2,200.f/2);
	glEnd();
	glColor3f(0,1,1);
	glBegin(GL_QUADS);	
		//left face
		glVertex3f(-200.f/2,200.f/2,200.f/2);
		glVertex3f(-200.f/2,200.f/2,-200.f/2);
		glVertex3f(-200.f/2,-200.f/2,-200.f/2);
		glVertex3f(-200.f/2,-200.f/2,200.f/2);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_QUADS);	
		//front face
		glVertex3f(200.f/2,200.f/2,-200.f/2);
		glColor3f(1,0,0);
		glVertex3f(-200.f/2,200.f/2,-200.f/2);
		glColor3f(1,0,1);
		glVertex3f(-200.f/2,-200.f/2,-200.f/2);
		glColor3f(1,1,0);
		glVertex3f(200.f/2,-200.f/2,-200.f/2);
		glColor3f(0,1,1);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_QUADS);	
		//right face
		glVertex3f(200.f/2,200.f/2,-200.f/2);
		glVertex3f(200.f/2,200.f/2,200.f/2);
		glVertex3f(200.f/2,-200.f/2,200.f/2);
		glVertex3f(200.f/2,-200.f/2,-200.f/2);
	glEnd();
	glColor3f(1,0,1);
	glBegin(GL_QUADS);			//top face
		glVertex3f(200.f/2,200.f/2,200.f/2);
		glVertex3f(-200.f/2,200.f/2,200.f/2);
		glVertex3f(-200.f/2,200.f/2,-200.f/2);
		glVertex3f(200.f/2,200.f/2,-200.f/2);
	glEnd();
	glColor3f(1,1,0);
	glBegin(GL_QUADS);
		//bottom face
		glVertex3f(200.f/2,-200.f/2,200.f/2);
		glVertex3f(-200.f/2,-200.f/2,200.f/2);
		glVertex3f(-200.f/2,-200.f/2,-200.f/2);
		glVertex3f(200.f/2,-200.f/2,-200.f/2);
	glEnd();
}

void FPS :: Board :: draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	int width;
	int height;
	SDL_GetWindowSize(att_graphBoard->att_window, &width, &height);
	att_player->update(width, height, SDL_GetWindowFlags(att_graphBoard->att_window) & SDL_WINDOW_FULLSCREEN, att_graphBoard->getGravity());

	drawACube();
	att_graphBoard->draw(att_player->att_physPlayer->givePos());


	for (unsigned int i = 1 ; i < att_gameEnnemies.size() ; ++i)
		att_graphBoard->att_ennemies[i]->draw(att_physBoard->att_ennemies[i]->givePos(att_graphBoard->att_ennemies[i]->att_currentFrame), att_physBoard->att_ennemies[i]->giveRot());
	for (unsigned int i = 1 ; i < att_graphBoard->att_displayedItems.size() ; ++i)
		att_graphBoard->att_displayedItems[i]->draw(att_physBoard->att_ennemies[i]->givePos(att_graphBoard->att_ennemies[i]->att_currentFrame));

	att_player->draw();

	SDL_GL_SwapWindow(att_graphBoard->att_window);
}

void FPS :: Board :: spawnEnnemy() {
	att_gameEnnemies.emplace_back(new ::Ennemy(*att_gameEnnemies[0]));
	att_physBoard->att_ennemies.emplace_back(new Physic :: Ennemy(*att_physBoard->att_ennemies[0]));
	att_graphBoard->att_ennemies.emplace_back(new Graphic :: Ennemy(att_graphBoard->att_ennemies[0]));
}

void FPS :: Board :: update() {
	unsigned int usableItem(att_player->att_physPlayer->update(att_physBoard->att_items, att_physBoard->att_ennemies, att_physBoard->att_levels[att_physBoard->att_curLevel]));
	for (unsigned int i = 1 ; i < att_gameEnnemies.size() ; ++i) {
		att_physBoard->att_ennemies[i]->update(att_player->att_physPlayer->givePos(), att_physBoard->att_ennemies, att_physBoard->att_levels[att_physBoard->att_curLevel], att_graphBoard->getGravity(), att_graphBoard->att_ennemies[i]->att_currentFrame);
		if (att_graphBoard->att_ennemies[i]->update()) {
			//He died
			att_graphBoard->att_ennemies.erase(att_graphBoard->att_ennemies.begin() + i);
			delete att_graphBoard->att_ennemies[i];
			att_gameEnnemies.erase(att_gameEnnemies.begin() + i--);
			delete att_gameEnnemies[i];
			continue;
		}
		if ((att_physBoard->att_ennemies[i]->givePos(att_graphBoard->att_ennemies[i]->att_currentFrame) - att_player->att_physPlayer->givePos()).length() < 1.5f) {
			att_graphBoard->att_ennemies[i]->attack();
			att_player->att_gamePlayer->getHit(att_gameEnnemies[i]->getDamage());
		}
	}
	for (unsigned int i = 0 ; i < att_graphBoard->att_displayedItems.size() ; ++i) {
		att_graphBoard->att_displayedItems[i]->update(i == usableItem);
		if (i == usableItem) {
			// if (att_player->att_gamePlayer->use(*att_gameItems[i]))
			// 	att_graphBoard->att_displayedItems.push_back(att_player->att_gamePlayer->getCurrentWeapon() ? att_player->att_weapons[att_player->att_gamePlayer->getCurrentWeapon() - 1] : att_player->att_knife);
			if (att_gameItems[i]->use() < 0) {
				(att_player->att_gamePlayer->getCurrentWeapon() ? att_player->att_weapons[att_player->att_gamePlayer->getCurrentWeapon() - 1] : att_player->att_knife) = (Graphic :: Weapon *) att_gameItems[i];
				att_graphBoard->att_displayedItems.erase(att_graphBoard->att_displayedItems.begin() + i);
			}
		}
	}

	if (!--att_timeSinceLastSpawn) {
		for (unsigned int i = 0 ; i < att_numberToSpawn ; ++i)
			spawnEnnemy();
		att_timeSinceLastSpawn = att_timeBeforeSpawn++;
		++att_numberToSpawn;
	}
	att_player->att_graphPlayer->draw(att_player->att_gamePlayer->getCurrentWeapon() ? att_player->att_weapons[att_player->att_gamePlayer->getCurrentWeapon() - 1] : att_player->att_knife);
	draw();
}

void FPS :: Board :: playerShoot(bool secondary) {
	float firstWallDistance(0);
	Vector3f particulePoint{0.f, 0.f, 0.f};
	Vector3f origin(att_player->att_physPlayer->givePos());
	Vector3f direction(att_player->att_graphPlayer->att_camera.getSight());
	for (unsigned int i = 0 ; i < att_physBoard->att_levels[att_physBoard->att_curLevel].size() ; ++i)
		Physic :: Collision :: rayBox(origin, direction, *att_physBoard->att_levels[att_physBoard->att_curLevel][i], &firstWallDistance, &particulePoint);
//	if (particulePoint != Vector3f(0.f, 0.f, 0.f))
//		att_graphBoard->att_levels[att_graphBoard->att_currentLevel]->spawnParticules(0, particulePoint, 5); //Wall
	for (unsigned int i = 1 ; i < att_physBoard->att_ennemies.size() ; ++i)
		if (att_physBoard->att_ennemies[i]->doesGetHit(origin, direction, &firstWallDistance, &particulePoint, att_graphBoard->att_ennemies[i]->att_currentFrame)) {
			if (att_gameEnnemies[i]->getHit(att_player->att_gamePlayer->getWeaponDamage()))
				att_graphBoard->att_ennemies[i]->die();
//			att_graphBoard->att_levels[att_graphBoard->att_currentLevel]->spawnParticules(1, particulePoint, 8); //Blood
		}	
}

void FPS :: Board :: run() {
	bool isRunning(true);
	Uint32 currentTimeTick(0); //FPS regulation
	SDL_Event event;
	bool isSecondaring(false);

	while (isRunning) {
		isSecondaring = false;
		currentTimeTick = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
				break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						att_player->att_gamePlayer->toAttack();
					if (event.button.button == SDL_BUTTON_RIGHT)
						isSecondaring = att_player->att_gamePlayer->secondary();
					att_player->att_graphPlayer->att_camera.isMouseIn() = true;
					SDL_ShowCursor(SDL_DISABLE);
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_LSHIFT:
							att_player->att_gamePlayer->sprint();
						break;
						case SDL_SCANCODE_SPACE:
							att_player->att_graphPlayer->jump();
						break;
						case SDL_SCANCODE_ESCAPE:
							isRunning = false; //Should have options and stuff
						break;
						case SDL_SCANCODE_R:
							att_player->reload();
						break;
						case SDL_SCANCODE_LALT:
							att_player->att_graphPlayer->att_camera.isMouseIn() = false;
							SDL_ShowCursor(SDL_ENABLE);
						break;
						default:
						break;
					}
				break;
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
						att_player->att_gamePlayer->stopSprint();
				break;
			}
		}
		if (isSecondaring) {
			att_player->secondary();
			playerShoot(true);
		}
		if (att_player->att_gamePlayer->attack()) {
			att_player->attack();
			playerShoot(false);
		}
		update();
		if (att_player->att_gamePlayer->getHealth() <= 0) {
			isRunning = false;
			std :: cout << "You lost" << std :: endl;
		}

		if (1000.0f/att_graphBoard->att_fps > SDL_GetTicks() - currentTimeTick) {
			SDL_Delay(1000./att_graphBoard->att_fps - (SDL_GetTicks() - currentTimeTick));
		}
	}
}

