#ifndef RV_ZD_GREITEM
#define RV_ZD_GREITEM

#include "Vector3f.hh"
#include <GL/gl.h>
//#include <GL/glu.h>

namespace Graphic {
	class Item {
	protected:
		GLuint att_outerLook;
		Vector3f att_rotation;
	public:
		Item(GLuint look, const Vector3f &rotation = {0.0f, 0.0f, 0.0f});
		Item(const Item *other) : att_outerLook(other->att_outerLook), att_rotation(other->att_rotation) {}
		void setRotation(const Vector3f &rot);
		virtual bool update(bool) {return true;}		//It looks stupid and IS stupid. But otherwhise copy of my displayedItems in Board gets rid of inheritance for 0 good reason
		virtual void draw(const Vector3f &) {}	//It looks stupid and IS stupid. But otherwhise copy of my displayedItems in Board gets rid of inheritance for 0 good reason. Hence I have to make it non virtual
		virtual ~Item() {}
	};
}

#endif