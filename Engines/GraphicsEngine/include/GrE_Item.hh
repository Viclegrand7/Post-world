#ifndef RV_ZD_GREITEM
#define RV_ZD_GREITEM

#include "Vector3f.hh"
#include <GL/gl.h>
//#include <GL/glu.h>

namespace Graphic {
	class Item {
	protected:
		GLuint att_outerLook;
		Vector3f att_position;
		Vector3f att_rotation;
	public:
		Item(GLuint look, const Vector3f &position = {0.0f, 0.0f, 0.0f}, const Vector3f &rotation = {0.0f, 0.0f, 0.0f});
		Item(const Item *other) : att_outerLook(other->att_outerLook), att_position(other->att_position), att_rotation(other->att_rotation) {}
		void setLocation(const Vector3f &pos);
		void setRotation(const Vector3f &rot);
		Vector3f &getLocation() {return att_position;}
		virtual bool update(bool) {return true;}		//It looks stupid and IS stupid. But otherwhise copy of my displayedItems in Board gets rid of inheritance for 0 good reason
		virtual void draw() {}							//It looks stupid and IS stupid. But otherwhise copy of my displayedItems in Board gets rid of inheritance for 0 good reason. Hence I have to make it non virtual
		virtual ~Item() {}
	};
}

#endif