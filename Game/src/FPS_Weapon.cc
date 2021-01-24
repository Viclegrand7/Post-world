#include "FPS_Weapon.hh"

bool FPS :: Weapon :: update() {
	return Graphic :: Weapon :: Grupdate(_isAuto && _isShooting);
}

bool FPS :: Weapon :: FPSattack() {
	if (:: Weapon :: attack()) {
		Grattack();
		return true;
	}
	return false;
}

bool FPS :: Weapon :: FPSsecondary() {
	if (:: Weapon :: secondary()) {
		Grsecondary();
		return true;
	}
	return false;
}

bool FPS :: Weapon :: FPSreload() {
	if (Grreload()) {
		:: Weapon :: reload();
		return true;
	}
	return false;
}
