#ifndef RV_ZD_FPSITEM
#define RV_ZD_FPSITEM

#include "GrE_Item.hh"
#include "PhE_Item.hh"
#include "Item.hh"

namespace FPS {
	class Item : virtual public Graphic :: Item, ::Item, Physic :: Item {
	public:
		bool update();
	};
}

#endif