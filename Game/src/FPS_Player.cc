#include "FPS_Player.hh"

void FPS :: Player :: draw() {
	att_graphPlayer->draw(att_gamePlayer->getCurrentWeapon() ? att_weapons[att_gamePlayer->getCurrentWeapon() - 1] : att_knife);
}

void FPS :: Player :: attack() {
	att_graphPlayer->attack(att_gamePlayer->getCurrentWeapon() ? att_weapons[att_gamePlayer->getCurrentWeapon() - 1] : att_knife);
}

void FPS :: Player :: secondary() {
	att_graphPlayer->secondary(att_gamePlayer->getCurrentWeapon() ? att_weapons[att_gamePlayer->getCurrentWeapon() - 1] : att_knife);
}

void FPS :: Player :: reload() {
	att_graphPlayer->reload(att_gamePlayer->getCurrentWeapon() ? att_weapons[att_gamePlayer->getCurrentWeapon() - 1] : att_knife);
}

void FPS :: Player :: update(int width, int height, bool isFullScreen, float gravity) {
	att_graphPlayer->update(att_physPlayer->givePos(), width, height, isFullScreen, att_gamePlayer->isRunning(), gravity);
	att_graphPlayer->att_camera.updateCamera(att_physPlayer->givePos());
}

