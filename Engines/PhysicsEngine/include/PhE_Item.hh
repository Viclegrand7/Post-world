#ifndef RV_ZD_PHEITEM
#define RV_ZD_PHEITEM

#include "PhE_CollisionSphere.hh"

namespace Physic {
	class Item {
		CollisionSphere att_hitBox;
	public:
		Item(const CollisionSphere &hb) : att_hitBox(hb) {}
		CollisionSphere &giveSphere() const {return att_hitBox;}
	};
}

#endif