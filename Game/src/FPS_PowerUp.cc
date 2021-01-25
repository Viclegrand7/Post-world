#include "FPS_PowerUp.hh"

bool FPS :: PowerUp :: update() {
	return att_graphPowerUp->update(isUsed);
}

bool &FPS :: PowerUp :: isUsed() {
	return isUsed;
}

void FPS :: PowerUp :: draw() {
	att_graphPowerUp->draw(att_physItem->givePos());
}