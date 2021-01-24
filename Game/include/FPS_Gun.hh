#ifndef RV_ZD_FPSGUN
#define RV_ZD_FPSGUN

#include "GrE_Gun.hh"
#include "Gun.hh"
#include "FPS_Weapon.hh"

namespace FPS {
	class Gun : virtual public Graphic :: Gun, ::Gun, FPS :: Weapon {
	public:
		bool FPSattack();
		bool FPSsecondary();
		bool FPSreload();
	};
}

#endif