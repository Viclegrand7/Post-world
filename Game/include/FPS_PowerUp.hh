#ifndef RV_ZD_FPSPOWERUP
#define RV_ZD_FPSPOWERUP

#include "FPS_Item.hh"
#include "GrE_PowerUp.hh"
#include "PowerUp.hh"

namespace FPS {
	class PowerUp : public Item {
		bool att_isUsed;
	public:
		Graphic :: PowerUp *att_graphPowerUp;
		::PowerUp *att_gamePowerUp;
		//Physic :: Item *

		bool update();
		void draw();
		bool &isUsed();
	};
}

#endif