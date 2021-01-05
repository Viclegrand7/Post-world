#ifndef RV_ZD_GREPARTICULE
#define RV_ZD_GREPARTICULE

#include <GL/gl.h>
#include "Vector3f.hh"
#include <random>


#include <iostream>

namespace Graphic {
	class Particule {
		GLuint att_visual; //The glList to call
		Vector3f att_position; //Where the particule is
		Vector3f att_direction; //Where it goes
		Vector3f att_rotation; //Some rotation to it
		Vector3f att_rotationAdd; //Some rotation to it
		unsigned int att_length; //How much time left
		static std::default_random_engine att_generator;
		static std::uniform_int_distribution<int> att_distribution;
	public:
		Particule(GLuint visual, unsigned int duration = 10, const Vector3f &pos = {0.f, 0.f, 0.f}) 
		: att_visual(visual), att_position(pos), att_direction(), att_rotation(), att_rotationAdd(),
		 att_length(duration) {
			att_direction = {(float) att_distribution(att_generator), (float) att_distribution(att_generator), (float) att_distribution(att_generator)};
			att_rotationAdd = {(float) att_distribution(att_generator), (float) att_distribution(att_generator), (float) att_distribution(att_generator)};
			att_direction.normalize();
			att_direction /= 5.0f;
		}
		Particule(const Particule *other, const Vector3f &pos)
		: att_visual(other->att_visual), att_position(pos), att_direction(), att_rotation(other->att_rotation), att_rotationAdd(), 
			att_length(other->att_length) {
			att_direction = {(float) att_distribution(att_generator), (float) att_distribution(att_generator), (float) att_distribution(att_generator)};
			att_rotationAdd = {(float) att_distribution(att_generator), (float) att_distribution(att_generator), (float) att_distribution(att_generator)};
			att_direction.normalize();
			att_direction /= 5.0f;
		}
		void draw();
		bool update();
		~Particule() {}
	};

}

#endif