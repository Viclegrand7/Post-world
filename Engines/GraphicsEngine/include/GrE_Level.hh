#ifndef RV_ZD_GRELEVEL
#define RV_ZD_GRELEVEL

#include <GL/gl.h>
#include <vector>
#include "Vector3f.hh"
#include "GrE_Particule.hh"

namespace Graphic {
	class Level {
		std :: vector <GLuint> att_setup;			//Background, obstacles,...
		std :: vector <Particule *> att_particules;		//Possible particles
		std :: vector <Particule *> att_curParticules;	//Current Particles
	public:
		Level(const std :: vector <GLuint> &setup, std :: vector <Particule*> particules) 
		: att_setup(setup), att_particules(particules), att_curParticules() {}
		void draw();
		void spawnParticules(unsigned int particule, const Vector3f &pos, int number = 0);
		void update();
	};
}

#endif