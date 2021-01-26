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
	if (att_graphPlayer->reload(att_gamePlayer->getCurrentWeapon() ? att_weapons[att_gamePlayer->getCurrentWeapon() - 1] : att_knife))
		att_gamePlayer->reload();
}

void FPS :: Player :: update(int width, int height, bool isFullScreen, float gravity) {
	att_graphPlayer->update(att_physPlayer->givePos(), width, height, isFullScreen, att_gamePlayer->isRunning(), gravity);
	att_graphPlayer->att_camera.updateCamera(att_physPlayer->givePos());
	if (att_gamePlayer->getCurrentWeapon()) {
		att_gamePlayer->update();
		if (att_graphPlayer->update(att_weapons[att_gamePlayer->getCurrentWeapon() - 1], att_gamePlayer->isAutoAndShooting()))
			att_gamePlayer->reset();
	}
	else {
		att_gamePlayer->update();
		if (att_graphPlayer->update(att_gamePlayer->getCurrentWeapon() ? att_weapons[att_gamePlayer->getCurrentWeapon() - 1] : att_knife, att_gamePlayer->isAutoAndShooting()))
			att_gamePlayer->reset();
	}
}

FPS :: Player :: Player(Graphic :: Weapon *knife, std :: vector <Graphic :: Weapon *> weapons, ::Melee *gknife, std :: vector <::Weapon *>pweapons)
: att_knife(knife), att_weapons(weapons), att_graphPlayer(new Graphic :: Player()), att_physPlayer(new Physic :: Player()), att_gamePlayer(new ::Player(gknife, pweapons)) {}