#include "FPS_Gun.hh"

bool FPS :: Gun :: update() {
	att_gameItem->countDown();
	if (att_graphItem->update(att_gameItem->isAuto() && att_gameItem->isShooting())) {
		att_gameItem->isReloading() = false; //We are done with an animation
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSattack() {
	if (att_gameItem->attack()) {
		att_graphItem->attack();
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSsecondary() {
	if (att_gameItem->secondary()) {
		att_graphItem->secondary();
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSreload() {
	if (att_graphItem->reload()) {
		att_gameItem->reload();
		return true;
	}
	return false;
}
