#ifndef RV_ZD_GREENNEMY
#define RV_ZD_GREENNEMY

#include <GL/gl.h>
#include <vector>
#include "Vector3f.hh"

namespace Graphic {
	class Ennemy {
		std :: vector <GLuint> att_frames;
		unsigned int att_walkAnimation; //Length of walking animation
		unsigned int att_attackAnimation; //Length of attackAnimation
		unsigned int att_deathAnimation; //Length of secondary. Secondary = reload / strong attack (melee)
		unsigned int att_currentFrame; //Where we're at. 0->normal-1: Normal. normal->normal+attack-1: attacking. normal+attack->frames.size()-1: secondary. frames.size(): outerLook
		bool att_doesAttack;
		bool att_doesDie;
	public:
		Ennemy(const std :: vector <GLuint> &frames, unsigned int walk, unsigned int attack, unsigned int die)
		: att_frames(frames), att_walkAnimation(walk), att_attackAnimation(attack), att_deathAnimation(die), att_currentFrame(0) {}
		Ennemy(const Ennemy *other)	: att_frames(other->att_frames), att_walkAnimation(other->att_walkAnimation), 
			att_attackAnimation(other->att_attackAnimation), att_deathAnimation(other->att_deathAnimation), att_currentFrame(0) {}
		void draw(const Vector3f &pos, const Vector3f &rot);
		bool update();
		void die();
		bool attack();
	};
}

#endif