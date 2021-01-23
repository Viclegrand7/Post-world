#ifndef RV_ZD_FPSWEAPON
#define RV_ZD_FPSWEAPON

#include "GrE_Weapon.hh"
#include "Weapon.hpp"

namespace FPS {
	class Weapon : public Graphic :: Weapon, Game :: Weapon {
	public:
		virtual bool attack();
		virtual bool secondary();
		virtual void reload();
	};
}

#endif