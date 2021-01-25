#include "FPS_Item.hh"

bool FPS :: Item :: update() {
	return true;
}

void FPS :: Item :: draw() {
	att_graphItem->draw(att_physItem->givePos());
}