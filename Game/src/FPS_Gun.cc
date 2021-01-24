#include "FPS_Gun.hh"

bool FPS :: Gun :: FPSattack() {
	if (attack()) {
		Grattack();
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSsecondary() {
	if (secondary()) {
		Grsecondary();
		return true;
	}
	return false;
}

bool FPS :: Gun :: FPSreload() {
	if (Grreload()) {
		reload();
		return true;
	}
	return false;
}
