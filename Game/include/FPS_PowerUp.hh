#ifndef RV_ZD_FPSPOWERUP
#define RV_ZD_FPSPOWERUP

#include "FPS_Item.hh"
#include "GrE_PowerUp.hh"
#include "PowerUp.hh"

namespace FPS {
	class PowerUp : virtual public Graphic :: PowerUp, ::PowerUp, public Item {
		bool isUsed;
	public:
		bool update();
	};
}

#endif