#ifndef RV_ZD_FPSMELEE
#define RV_ZD_FPSMELEE

#include "GrE_Weapon.hh"
#include "Melee.hh"
#include "FPS_Weapon.hh"

namespace FPS {
	class Melee : public Weapon {
	public:
		Graphic :: Weapon *att_graphMelee;
		::Melee *att_gameMelee;

		bool update();
		bool FPSattack();
		bool FPSsecondary();
		bool FPSreload();
	};
}

#endif