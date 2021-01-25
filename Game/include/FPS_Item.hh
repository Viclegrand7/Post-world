#ifndef RV_ZD_FPSITEM
#define RV_ZD_FPSITEM

#include "GrE_Item.hh"
#include "PhE_Item.hh"
#include "Item.hh"

namespace FPS {
	class Item {
	public:
		Graphic :: Item *att_graphItem;
		Physic :: Item *att_physItem;
		::Item *att_gameItem;

		virtual bool update();
		virtual void draw();
	};
}

#endif