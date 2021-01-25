#include "FPS_Melee.hh"

bool FPS :: Melee :: update() {
	att_gameMelee->countDown();
	if (att_graphMelee->update(att_gameMelee->isAuto() && att_gameMelee->isShooting())) {
		return true;
	}
	return false;
}

bool FPS :: Melee :: FPSattack() {
	if (att_gameMelee->attack()) {
		att_graphMelee->attack();
		return true;
	}
	return false;
}

bool FPS :: Melee :: FPSsecondary() {
	if (att_gameMelee->secondary()) {
		att_graphMelee->secondary();
		return true;
	}
	return false;
}

bool FPS :: Melee :: FPSreload() {
	return false;
}
