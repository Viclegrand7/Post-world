#ifndef RV_ZD_GREGUN
#define RV_ZD_GREGUN

#include <GL/gl.h>
//#include <GL/glu.h>
#include <vector>
#include "GrE_Weapon.hh"
#include "Vector3f.hh"

namespace Graphic {
	class Gun : public Weapon {
	protected:
		Vector3f att_aimPosition; //Where to place the gun when aiming
		Vector3f att_curPosition; //Basically: Are we aiming or not?
		Vector3f att_aimRotation; //How to rotate the gun when aiming
		Vector3f att_curRotation; //Basically: Are we aiming or not?
		bool isAiming;
	public:
		Gun(const std :: vector <GLuint> &frames = {0}, unsigned int na = 0, unsigned int aa = 0, unsigned int sa = 0,
		const Vector3f &aimPos = {-0.01f, -0.4f, -1.5f}, const Vector3f &aimRot = {1.f, -1.f, 0.35f}, 
			const Vector3f &position = {0.f, -0.9f, -2.0f}, const Vector3f &rotation = {0.0f, 10.0f, 3.0f})
		: Weapon(frames, na, aa, sa, position, rotation), att_aimPosition(aimPos), att_curPosition(position), att_aimRotation(aimRot), 
			att_curRotation(rotation), isAiming(false) {}
		bool attack();
		bool secondary();
		bool reload();
		void draw(const Vector3f &);	//Not in hands
		void draw(bool);				//In hands
		bool update(bool isAutoAndShooting);
		~Gun() {}
	};

}

#endif