#include "FPS_Board.hh"

void FPS :: Board :: draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	att_graphBoard->draw(att_player->att_physPlayer->givePos());
	for (unsigned int i = 0 ; i < att_gameEnnemies.size() ; ++i)
		att_graphBoard->att_ennemies[i]->draw(att_physBoard->att_ennemies[i]->givePos());
	for (unsigned int i = 0 ; i < att_graphBoard->att_displayedItems.size() ; ++i)
		att_graphBoard->att_displayedItems[i]->draw(att_physBoard->att_ennemies[i]->givePos());

	att_player->draw();

	SDL_GL_SwapWindow(att_graphBoard->att_window);
}

void FPS :: Board :: spawnEnnemy() {
	att_gameEnnemies.emplace_back(new ::Ennemy(att_gameEnnemies[0]));
	att_physBoard.emplace_back(new Physic :: Ennemy(att_physBoard->att_ennemies[0]));
	att_graphBoard.emplace_back(new Graphic :: Ennemy(att_graphBoard->att_ennemies[0]));
}

void FPS :: Board :: update() {
	int width;
	int height;
	SDL_GetWindowSize(window, &width, &height);
	att_player->update(width, height, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN, att_graphBoard->getGravity());
	unsigned int usableItem(att_player->att_physPlayer->update(att_physBoard->att_ennemies, att_physBoard->att_levels[att_physBoard->att_currentLevel], att_physBoard->att_items));
	for (unsigned int i = 1 ; i < att_gameEnnemies.size() ; ++i) {
		att_graphBoard->att_ennemies[i]->update();
		if (att_physBoard->att_ennemies[i]->update(att_player->att_physPlayer->givePos(), att_physBoard->att_ennemies)) {
			//He died
			att_graphBoard->att_ennemies.erase(att_graphBoard->att_ennemies.begin() + i);
			att_gameEnnemies.erase(att_gameEnnemies.begin() + i--);
		}
	}
	for (unsigned int i = 0 ; i < att_graphBoard->att_items.size() ; ++i)
		att_graphBoard->att_items[i]->update();

	if (!--att_timeSinceLastSpawn) {
		for (unsigned int i = 0 ; i < att_numberToSpawn ; ++i)
			spawnEnnemy();
		att_timeSinceLastSpawn = att_timeBeforeSpawn++;
		++att_numberToSpawn;
	}

	draw();
}

void FPS :: Board :: run() {
	bool isRunning(true);
	Uint32 currentTimeTick(0); //FPS regulation
	SDL_Event event;

	while (isRunning) {
		currentTimeTick = SDL_GetTicks();

		while (SDL_PollEvent(&event))
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
				break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						att_player->att_gamePlayer->setAttack();
					if (event.button.button == SDL_BUTTON_RIGHT)
						att_player->att_gamePlayer->setSecondary();
					player.att_camera.isMouseIn() = true;
					SDL_ShowCursor(SDL_DISABLE);
				break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_LSHIFT:
							isSprinting = true;
						break;
						case SDL_SCANCODE_SPACE:
							player.jump();
						break;
						case SDL_SCANCODE_ESCAPE:
							isRunning = false;
						break;
						case SDL_SCANCODE_O:
							myLevel.spawnParticules(1, player.att_camera.getLocation() + 10 * player.att_camera.getSight(), 10);
						break;
						case SDL_SCANCODE_L:
							myLevel.spawnParticules(0, player.att_camera.getLocation() + 10 * player.att_camera.getSight(), 5);
						break;
						case SDL_SCANCODE_R:
							pistol->reload();
						break;
						// case SDL_SCANCODE_I:
						// 	++pistol_g.getLocation().att_z;
						// break;
						// case SDL_SCANCODE_K:
						// 	--pistol_g.getLocation().att_z;
						// break;
						// case SDL_SCANCODE_L:
						// 	++pistol_g.getLocation().att_x;
						// break;
						// case SDL_SCANCODE_J:
						// 	--pistol_g.getLocation().att_x;
						// break;
						case SDL_SCANCODE_LALT:
							player.att_camera.isMouseIn() = false;
							SDL_ShowCursor(SDL_ENABLE);
						default:
						break;
					}
				break;
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
						isSprinting = false;
				break;
			}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		SDL_GetWindowSize(window, &width, &height);
		player.update(width, height, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN, isSprinting, 0.f);
		player.att_camera.updateCamera();
		if (somePowerUp.update(tryExplode))
			tryExplode = false;
		pistol->update(false);
		myLevel.update();

//		glCallList(myGun);

		glCallList(someDrawing);
		myLevel.draw();
		somePowerUp.draw();
//		glClear(GL_DEPTH_BUFFER_BIT); //Activate this if want my weapons to be seen through walls
		player.draw(pistol);


		if (1000.0f/myFPS > SDL_GetTicks() - currentTimeTick) {
			SDL_Delay(1000./myFPS - (SDL_GetTicks() - currentTimeTick));
		}
	}

}