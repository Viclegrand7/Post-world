#ifndef RV_ZD_GREWEAPON
#define RV_ZD_GREWEAPON

#include <GL/gl.h>
//#include <GL/glu.h>
#include <vector>
#include "GrE_Item.hh"
#include "Vector3f.hh"

namespace Graphic {
	class Weapon : public Item {
	protected:
		std :: vector <GLuint> att_frames;
		unsigned int att_normalAnimation; //Length of animation
		unsigned int att_attackAnimation; //Length of attackAnimation
		unsigned int att_secondaryAnimation; //Length of secondary. Secondary = reload / strong attack (melee)
		unsigned int att_currentFrame; //Where we're at. 0->normal-1: Normal. normal->normal+attack-1: attacking. normal+attack->frames.size()-1: secondary. frames.size(): outerLook
	public:
		Weapon(const std :: vector <GLuint> &frames = {}, unsigned int na = 0, unsigned int aa = 0, unsigned int sa = 0,
			const Vector3f &position = {0.8f, -0.3f, -2.0f}, const Vector3f &rotation = {0.0f, 10.0f, 5.0f}, unsigned int curFrame = 0)
		: Item(frames[0], position, rotation), att_frames(frames), att_normalAnimation(na),
			att_attackAnimation(aa), att_secondaryAnimation(sa), att_currentFrame(curFrame) {}
		Weapon(const Weapon *other) : Item(other->att_outerLook, other->att_position, other->att_rotation), att_frames(other->att_frames), att_normalAnimation(other->att_normalAnimation),
			att_attackAnimation(other->att_attackAnimation), att_secondaryAnimation(other->att_secondaryAnimation), att_currentFrame(other->att_currentFrame) {}
		virtual void draw();
		virtual bool update(bool isAutoAndAttacking);
		virtual void attack();
		virtual void reload();
		virtual void secondary();
		virtual ~Weapon() {}
	};

}

#endif