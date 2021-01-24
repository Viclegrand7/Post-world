#ifndef RV_ZD_FPSGUN
#define RV_ZD_FPSGUN

#include "GrE_Gun.hh"
#include "Gun.hpp"

namespace FPS {
	class Gun : public Graphic :: Gun, Game :: Gun {
	public:
		bool attack();
		bool secondary();
		void reload();
	};
}

#endif