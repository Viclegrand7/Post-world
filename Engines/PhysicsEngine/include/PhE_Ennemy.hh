#ifndef RV_ZD_PHEENNEMY
#define RV_ZD_PHEENNEMY

#include "PhE_CollisionSphere.hh"
#include "PhE_CollisionBox.hh"
#include "PhE_Collision.hh"
#include <vector>

namespace Physic {
	class Ennemy {
		std :: vector <CollisionSphere>att_head;
		std :: vector <CollisionBox>att_torso;
		std :: vector <CollisionBox>att_legs1;
		std :: vector <CollisionBox>att_arms1;
		std :: vector <CollisionBox>att_legs2;
		std :: vector <CollisionBox>att_arms2;
		std :: vector <CollisionSphere>att_fakeBox;
		Vector3f att_rotation;
		float att_speed;

		void testCollisionWall(const std :: vector<CollisionQuad *> &walls, unsigned int curFrame);
		void testCollisionTeamates(const std :: vector<Ennemy *> &ennemies, unsigned int curFrame);
		void moveDir(const Vector3f &other);
	public:
		Ennemy() : att_head{Physic :: CollisionSphere()}, att_torso{Physic :: CollisionBox()}, att_legs1{Physic :: CollisionBox()}, 
			att_arms1{Physic :: CollisionBox()}, att_legs2{Physic :: CollisionBox()}, att_arms2{Physic :: CollisionBox()}, 
			att_fakeBox{Physic :: CollisionSphere()}, att_rotation{}, att_speed{0.1f} {}
		Ennemy(CollisionSphere h, CollisionBox t, CollisionBox l1, CollisionBox l2, CollisionBox a1, CollisionBox a2, CollisionSphere fhb)
			: att_head{h}, att_torso{t}, att_legs1{l1}, att_arms1{a1}, att_legs2{l2}, att_arms2{a2}, att_fakeBox{fhb}, att_rotation{0.f, 0.f, 0.f}, att_speed(0.1f) {}
		Ennemy &operator+=(const Ennemy &other);
		Ennemy &operator=(const Ennemy &other);
		void equals(const Physic :: CollisionSphere &sphere, bool isHead);
		void equals(const Physic :: CollisionBox &box, char isWhat);
		CollisionSphere giveSphere() {return att_fakeBox[0];}
		Vector3f &giveRot() {return att_rotation;}
		bool doesGetHit(const Vector3f &pos, const Vector3f &dir, float *dis, Vector3f *collisionPoint, unsigned int curFrame);
		void update(const Vector3f &character, const std :: vector<Ennemy *> &ennemies, const std :: vector <CollisionQuad *> &wall, float gravity, unsigned int curFrame);
		Vector3f givePos(unsigned int curFrame) {return att_fakeBox[curFrame].att_center;}
	};
}

#endif