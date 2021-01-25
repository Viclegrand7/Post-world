#include "FPS_PowerUp.hh"

bool FPS :: PowerUp :: update() {
	return att_graphPowerUp->update(att_isUsed);
}

bool &FPS :: PowerUp :: isUsed() {
	return att_isUsed;
}

void FPS :: PowerUp :: draw() {
	att_graphPowerUp->draw(att_physItem->givePos());
}