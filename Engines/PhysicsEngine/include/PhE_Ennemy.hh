#ifndef RV_ZD_PHEENNEMY
#define RV_ZD_PHEENNEMY

#include "PhE_CollisionSphere.hh"
#include "PhE_CollisionBox.hh"
#include "PhE_Obstacle.hh"
#include <vector>

namespace Physic {
	class Ennemy {
		CollisionSphere att_head;
		CollisionBox att_torso;
		CollisionBox att_legs[2];
		CollisionBox att_arms[2];
		CollisionSphere att_fakeBox;
		Vector3f att_rotation;
		float att_speed;

		void testCollisionWall(const std :: vector<CollisionBox *> &walls);
		void testCollisionTeamates(const std :: vector<Ennemy *> &ennemies);
		void moveDir(const Vector3f &other);
	public:
		Ennemy(const CollisionSphere &h, const CollisionBox &t, const CollisionBox &l[2], const CollisionBox &a[2], const CollisionSphere &fhb)
		: att_head(h), att_torso(t), att_legs(l), att_arms(a), att_fakeBox(fhb), att_rotation{0.f, 0.f, 0.f}, att_speed(0.1f) {}
		CollisionSphere giveSphere() {return att_fakeBox;}
		Vector3f &giveRot() {return att_rotation;}
		bool doesGetHit(const Vector3f &pos, const Vector3f &dir, float &dis, Vector3f &collisionPoint);
		void update(const Vector3f &character, const std :: vector<Ennemy *> &ennemies, const std :: vector <CollisionBox *> &wall, float gravity);
	};
}

#endif