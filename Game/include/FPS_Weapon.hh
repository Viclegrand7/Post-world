#ifndef RV_ZD_FPSWEAPON
#define RV_ZD_FPSWEAPON

#include "GrE_Weapon.hh"
#include "Weapon.hh"
#include "FPS_Item.hh"

namespace FPS {
	class Weapon : public Graphic :: Weapon, ::Weapon, FPS :: Item {
	public:
		bool update();
		virtual bool FPSattack();
		virtual bool FPSsecondary();
		virtual bool FPSreload();
	};
}

#endif