#include "FPS_Gun.hh"

bool FPS :: Gun :: attack() {
	if (Game :: Gun :: attack()) {
		Graphic :: Gun :: attack();
		return true;
	}
	return false;
}

bool FPS :: Gun :: secondary() {
	if (Game :: Gun :: secondary()) {
		Graphic :: Gun :: secondary();
		return true;
	}
	return false;
}

void FPS :: Gun :: reload() {
	if (Game :: Gun :: reload())
		Graphic :: Gun :: reload();
}
