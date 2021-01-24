#include "FPS_Weapon.hh"

bool FPS :: Weapon :: update() {
	return update(_isAuto && _isShooting);
}

bool FPS :: Weapon :: FPSattack() {
	if (attack()) {
		Grattack();
		return true;
	}
	return false;
}

bool FPS :: Weapon :: FPSsecondary() {
	if (secondary()) {
		Grsecondary();
		return true;
	}
	return false;
}

bool FPS :: Weapon :: FPSreload() {
	if (Grreload()) {
		reload();
		return true;
	}
	return false;
}
