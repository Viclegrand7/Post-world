#include "GrE_Player.hh"


bool Graphic :: Player :: update(Vector3f &location, int width, int height, bool isFullScreen, bool isRunning, float gravity) {
	bool doneJumping(false);
	if (isRunning)
		doneJumping = att_camera.control(location, width, height, isFullScreen, att_sprintSpeed, gravity);
	else 
		doneJumping = att_camera.control(location, width, height, isFullScreen, att_speed, gravity);
	if (att_camera.isMoving()) {
		att_head = att_head < 40 ? att_head + 1 : 0;

		if (att_head < 10) { //->up-right
			att_camera.lookAt(att_camera.getPitch() + att_head * (0.00390625f * !isRunning + 0.015625f * isRunning), att_camera.getYaw() + (att_head - 10) * (0.00390625f * !isRunning + 0.015625f * isRunning) );
		}
		else if (att_head < 20) { //->down-right
			att_camera.lookAt(att_camera.getPitch() + (20 - att_head) * (0.00390625f * !isRunning + 0.015625f * isRunning), att_camera.getYaw() + (att_head - 10) * (0.00390625f * !isRunning + 0.015625f * isRunning));
		}
		else if (att_head < 30) { //->down-left
			att_camera.lookAt(att_camera.getPitch() + (20 - att_head) * (0.00390625f * !isRunning + 0.015625f * isRunning), att_camera.getYaw() + (30 - att_head) * (0.00390625f * !isRunning + 0.015625f * isRunning));
		}
		else { //->up-left
			att_camera.lookAt(att_camera.getPitch() + (att_head - 40) * (0.00390625f * !isRunning + 0.015625f * isRunning), att_camera.getYaw() + (30 - att_head) * (0.00390625f * !isRunning + 0.015625f * isRunning));
		}
	// /512 if walking, /128 if running
	}
	return doneJumping;
}

void Graphic :: Player :: draw(Weapon *weapon) {
	weapon->draw(true);
}

void Graphic :: Player :: attack(Weapon *weapon) {
	weapon->Grattack();
}

void Graphic :: Player :: secondary(Weapon *weapon) {
	weapon->Grsecondary();
}

void Graphic :: Player :: reload(Weapon *weapon) {
	weapon->Grreload();
}

void Graphic :: Player :: jump() {
	att_camera.jump();
}