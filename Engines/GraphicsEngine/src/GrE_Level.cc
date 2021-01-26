#include "GrE_Level.hh"

void Graphic :: Level :: draw() {
		glCallList(att_setup);
	for (unsigned int i = 0 ; i < att_curParticules.size() ; ++i)
		att_curParticules[i]->draw();
}

void Graphic :: Level :: spawnParticules(unsigned int particule, const Vector3f &pos, int number) {
	for (int i = 0 ; i < number ; ++i) 
		att_curParticules.emplace_back(new Particule(att_particules[particule], pos)); //New particule to be drawn
}

void Graphic :: Level :: update() {
	for (std :: vector <Graphic :: Particule *> :: iterator it = att_curParticules.begin() ; it != att_curParticules.end() ; ++it)
		if ((*it)->update()) {//If it reached it's end of life
			delete *it;
			att_curParticules.erase(it--); //We remove from current and go back (so we can go next with the loop)
		}
}
