#include "FPS_Weapon.hh"

bool FPS :: Weapon :: update() {
	return att_graphWeapon->update(att_gameWeapon->isAuto() && att_gameWeapon->isShooting());
}

// bool FPS :: Weapon :: FPSattack() {
// 	if (:: Weapon :: attack()) {
// 		Graphic :: Weapon :: attack();
// 		return true;
// 	}
// 	return false;
// }

// bool FPS :: Weapon :: FPSsecondary() {
// 	if (:: Weapon :: secondary()) {
// 		Graphic :: Weapon :: secondary();
// 		return true;
// 	}
// 	return false;
// }

// bool FPS :: Weapon :: FPSreload() {
// 	if (Graphic :: Weapon :: reload()) {
// 		:: Weapon :: reload();
// 		return true;
// 	}
// 	return false;
// }
