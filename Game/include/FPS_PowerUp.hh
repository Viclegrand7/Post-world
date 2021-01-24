#ifndef RV_ZD_FPSPOWERUP
#define RV_ZD_FPSPOWERUP

#include "GrE_PowerUp.hh"
#include "PowerUp.hpp"

namespace FPS {
	class PowerUp : public Graphic :: PowerUp, Game :: PowerUp {
		bool isUsed;
	public:
	};
}

#endif