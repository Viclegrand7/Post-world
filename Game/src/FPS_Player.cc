#include "FPS_Player.hh"

void FPS :: Player :: draw() {
	draw(currentWeapon ? weapons[currentWeapon - 1] : knife);
}