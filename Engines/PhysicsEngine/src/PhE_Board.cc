#include "PhE_Board.hh"

#include <iostream>

// std :: vector<Vector3f> Physic :: Board :: playerShoot(const Vector3f &dir) {
// 	float firstWallDistance(0);
// 	Vector3f particulePoint{0.f, 0.f, 0.f};
// 	Vector3f origin(att_player->givePos());
// 	for (unsigned int i = 0 ; i < att_levels[att_curLevel].size() ; ++i)
// 		Physic :: Collision :: rayBox(origin, dir, *att_levels[att_curLevel][i], &firstWallDistance, &particulePoint);
// 	std :: vector <Vector3f> particulesToSpawn{particulePoint};
// 	for (unsigned int i = 0 ; i < att_ennemies.size() ; ++i)
// 		if (att_ennemies[i]->doesGetHit(origin, dir, &firstWallDistance, &particulePoint)) {
// 			std :: cout << i << " got hit" << std :: endl;
// 			particulesToSpawn.push_back(particulePoint);
// 		}
// 	return particulesToSpawn;
// }
//Should not exist. Will be done in the Game, no engines. Gives the collisionPoints, the ennemies hit, what particules to draw. Intervenes with litterally all 3 engines

void Physic :: Board :: changeLevel(unsigned int level) {
	att_curLevel = level;
}
