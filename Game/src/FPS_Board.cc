#include "FPS_Board.hh"
#include "PhE_Collision.hh"

#include <iostream>

void FPS :: Board :: draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	att_graphBoard->draw(att_player->att_physPlayer->givePos());
	for (unsigned int i = 0 ; i < att_gameEnnemies.size() ; ++i)
		att_graphBoard->att_ennemies[i]->draw(att_physBoard->att_ennemies[i]->givePos(), att_physBoard->att_ennemies[i]->giveRot());
	for (unsigned int i = 0 ; i < att_graphBoard->att_displayedItems.size() ; ++i)
		att_graphBoard->att_displayedItems[i]->draw(att_physBoard->att_ennemies[i]->givePos());

	att_player->draw();

	SDL_GL_SwapWindow(att_graphBoard->att_window);
}

void FPS :: Board :: spawnEnnemy() {
	att_gameEnnemies.emplace_back(new ::Ennemy(*att_gameEnnemies[0]));
	att_physBoard->att_ennemies.emplace_back(new Physic :: Ennemy(*att_physBoard->att_ennemies[0]));
	att_graphBoard->att_ennemies.emplace_back(new Graphic :: Ennemy(att_graphBoard->att_ennemies[0]));
}

void FPS :: Board :: update() {
	int width;
	int height;
	SDL_GetWindowSize(att_graphBoard->att_window, &width, &height);
	att_player->update(width, height, SDL_GetWindowFlags(att_graphBoard->att_window) & SDL_WINDOW_FULLSCREEN, att_graphBoard->getGravity());
	unsigned int usableItem(att_player->att_physPlayer->update(att_physBoard->att_items, att_physBoard->att_ennemies, att_physBoard->att_levels[att_physBoard->att_curLevel]));
	for (unsigned int i = 1 ; i < att_gameEnnemies.size() ; ++i) {
		att_physBoard->att_ennemies[i]->update(att_player->att_physPlayer->givePos(), att_physBoard->att_ennemies, att_physBoard->att_levels[att_physBoard->att_curLevel], att_graphBoard->getGravity());
		if (att_graphBoard->att_ennemies[i]->update()) {
			//He died
			att_graphBoard->att_ennemies.erase(att_graphBoard->att_ennemies.begin() + i);
			att_gameEnnemies.erase(att_gameEnnemies.begin() + i--);
			continue;
		}
		if ((att_physBoard->att_ennemies[i]->givePos() - att_player->att_physPlayer->givePos()).length() < 0.5f) {
			att_graphBoard->att_ennemies[i]->attack();
			att_player->att_gamePlayer->getHit(att_gameEnnemies[i]->getDamage());
		}
	}
	for (unsigned int i = 0 ; i < att_graphBoard->att_items.size() ; ++i)
		i == usableItem ? att_graphBoard->att_items[i]->update(true) : att_graphBoard->att_items[i]->update(false);

	if (!--att_timeSinceLastSpawn) {
		for (unsigned int i = 0 ; i < att_numberToSpawn ; ++i)
			spawnEnnemy();
		att_timeSinceLastSpawn = att_timeBeforeSpawn++;
		++att_numberToSpawn;
	}

	draw();
}

void FPS :: Board :: playerShoot(bool secondary) {
	float firstWallDistance(0);
	Vector3f particulePoint{0.f, 0.f, 0.f};
	Vector3f origin(att_player->att_physPlayer->givePos());
	Vector3f direction(att_player->att_graphPlayer->att_camera.getSight());
	for (unsigned int i = 0 ; i < att_physBoard->att_levels[att_physBoard->att_curLevel].size() ; ++i)
		Physic :: Collision :: rayBox(origin, direction, *att_physBoard->att_levels[att_physBoard->att_curLevel][i], &firstWallDistance, &particulePoint);
	if (particulePoint != Vector3f(0.f, 0.f, 0.f))
		att_graphBoard->att_levels[att_graphBoard->att_currentLevel]->spawnParticules(0, particulePoint, 5); //Wall
	for (unsigned int i = 0 ; i < att_physBoard->att_ennemies.size() ; ++i)
		if (att_physBoard->att_ennemies[i]->doesGetHit(origin, direction, &firstWallDistance, &particulePoint)) {
			if (att_gameEnnemies[i]->getHit(att_player->att_gamePlayer->getWeaponDamage()))
				att_graphBoard->att_ennemies[i]->die();
			att_graphBoard->att_levels[att_graphBoard->att_currentLevel]->spawnParticules(1, particulePoint, 8); //Blood
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

		while (SDL_PollEvent(&event))
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
						case SDL_SCANCODE_LALT:
							att_player->att_graphPlayer->att_camera.isMouseIn() = false;
							SDL_ShowCursor(SDL_ENABLE);
						default:
						break;
					}
				break;
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
						att_player->att_gamePlayer->stopSprint();
				break;
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

