#ifndef RV_ZD_FPSWEAPON
#define RV_ZD_FPSWEAPON

#include "GrE_Weapon.hh"
#include "Weapon.hh"
#include "FPS_Item.hh"

namespace FPS {
	class Weapon : public Item {
	public:
		Graphic :: Weapon *att_graphWeapon;
		:: Weapon *att_gameWeapon;
		//Has Graphic :: Item *, Physic :: Item *, Game :: Item*
		virtual bool update();
		virtual bool FPSattack() = 0;
		virtual bool FPSsecondary() = 0;
		virtual bool FPSreload() = 0;
	};
}

#endif