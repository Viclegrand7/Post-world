#ifndef Vic_CHARACTER
#define Vic_CHARACTER
#include "Character.h"
#endif

#ifndef Vic_SPELLS
#define Vic_SPELLS
#include "Spells.h"
#endif

#ifndef Vic_STDLIB
#define Vic_STDLIB
#include <stdlib.h>
#endif

#ifndef Vic_TIME
#define Vic_TIME
#include <time.h>
#endif

#ifndef Vic_INVENTORY
#define Vic_INVENTORY
#include "Inventory.h"
#endif

#ifndef Vic_BOARD
#define Vic_BOARD
#include "Board.h"
#endif

int main() {
	srand(time(NULL));
	Board tableboard("Zedd", 20, 0, 65, 45, 50, 6, 1, 3, 5, 4);
	tableboard.createEnnemy("Vampire", 25, 0, 70, 50, 40, 6, 2, 3, 2, 4, 1);
	tableboard.createEnnemy("Bat", 6, 0);
	tableboard.createEnnemy("Bat", 6, 0);
	tableboard.createAlly("Adventurer", 10, 6);
	tableboard.addItemToPlayer(2, 6, 3);
	tableboard.addItemToPlayer(3, 4, 2);
	tableboard.addItemToPlayer(4, 5, 1);
	tableboard.addItemToPlayer(5, 0, 1);
	tableboard.playGame();
}