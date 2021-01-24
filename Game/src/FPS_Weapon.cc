#include "FPS_Weapon.hh"

bool attack() {
	if (Game :: Weapon :: attack()) {
		Graphic :: Weapon :: attack();
		return true;
	}
	return false;
}

bool secondary() {
	if (Game :: Weapon :: secondary()) {
		Graphic :: Weapon :: secondary();
		return true;
	}
	return false;
}

void reload() {
	if (Game :: Weapon :: reload()) {
		Graphic :: Weapon :: reload();
		return true;
	}
	return false;
}
