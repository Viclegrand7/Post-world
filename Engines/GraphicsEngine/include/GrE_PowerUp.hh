#ifndef RV_ZD_GREPOWERUP
#define RV_ZD_GREPOWERUP

#include "Vector3f.hh"
#include <GL/gl.h>
#include "GrE_Item.hh"
#include <vector>

namespace Graphic {
	class PowerUp : public Item {
	protected:
		std :: vector <GLuint> att_activationLook;
		unsigned int att_currentFrame;
	public:
		PowerUp(const std :: vector<GLuint> &activation, const Vector3f &rotation = {0.0f, 0.0f, 0.0f}, unsigned int cFrame = -1)
		: Item(activation[0], rotation), att_activationLook(activation), att_currentFrame(cFrame) 
		{
			if (att_currentFrame >= att_activationLook.size()) 
				att_currentFrame = att_activationLook.size();
		}
		PowerUp(const PowerUp *other) : Item(other->att_outerLook, other->att_rotation),
			att_activationLook(other->att_activationLook), att_currentFrame(other->att_currentFrame) {}
		void draw(const Vector3f &position);
		bool update(bool isPickedUp);
		~PowerUp() {}
	};
}

#endif