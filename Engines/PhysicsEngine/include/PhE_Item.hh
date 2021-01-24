#ifndef RV_ZD_PHEITEM
#define RV_ZD_PHEITEM

#include "PhE_CollisionSphere.hh"

namespace Physic {
	class Item {
		CollisionSphere att_hitBox;
	public:
		Item(const CollisionSphere &hb) : att_hitBox(hb) {}
		const CollisionSphere &giveSphere() const;
	};
}

#endif