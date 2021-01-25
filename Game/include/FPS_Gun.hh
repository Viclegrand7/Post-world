#ifndef RV_ZD_FPSGUN
#define RV_ZD_FPSGUN

#include "GrE_Gun.hh"
#include "Gun.hh"
#include "FPS_Weapon.hh"

namespace FPS {
	class Gun : public Weapon {
	public:
		Graphic :: Gun *att_graphGun;
		:: Gun *att_gameGun;
		
		bool update();
		bool FPSattack();
		bool FPSsecondary();
		bool FPSreload();
	};
}

#endif