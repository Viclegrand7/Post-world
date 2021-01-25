#include "FPS_Gun.hh"

bool FPS :: Gun :: update() {
	att_gameGun->countDown();
	if (att_graphGun->update(att_gameGun->isAuto() && att_gameGun->isShooting())) {
		att_gameGun->isReloading() = false; //We are done with an animation
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSattack() {
	if (att_gameGun->attack()) {
		att_graphGun->attack();
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSsecondary() {
	if (att_gameGun->secondary()) {
		att_graphGun->secondary();
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSreload() {
	if (att_graphGun->reload()) {
		att_gameGun->reload();
		return true;
	}
	return false;
}
