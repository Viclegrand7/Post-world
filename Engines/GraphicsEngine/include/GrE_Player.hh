#ifndef RV_ZD_GREPLAYER
#define RV_ZD_GREPLAYER

#include <vector>
#include "GrE_Camera.hh"
#include "GrE_Weapon.hh"

namespace Graphic {
	class Weapon;

	class Player {
		float att_head; //Make some head movement while we walk
		float att_speed;
		float att_sprintSpeed;
	public:
		Camera att_camera; //For simplicity reasons

		Player(Camera cam = Camera(), float speed = 0.2, float sprintSpeed = 0.5)
		: att_head(0), att_speed(speed), att_sprintSpeed(sprintSpeed), att_camera(cam) {}
		bool update(int width, int height, bool isFullScreen, bool isRunning, float gravity);
		void draw(Weapon *weapon);
		void attack(Weapon *weapon);
		void secondary(Weapon *weapon);
		void reload(Weapon *weapon);
		void jump();
	};
}

#endif