#ifndef RV_ZD_GRECAMERA
#define RV_ZD_GRECAMERA

#include "Vector3f.hh"
#include <vector>

namespace Graphic {
	class Camera {
	protected:
		float att_pitch;
		float att_yaw;
		float att_roll;
		float att_mouseSpeed;
	
		bool att_isMouseIn;
		bool att_isMoving;
		std :: vector <float> att_jumpPos;
		unsigned int att_currentJump;

		void lockCamera();
		void moveCamera(Vector3f &location, float direction, float speed);
		void moveCameraUp(Vector3f &location, float direction, float speed);
		void handleMoves(Vector3f &location, float speed);
	public:
		Camera(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f, float mouseSpeed = 0.5f)
			: att_pitch(pitch), att_yaw(yaw), att_roll(roll), att_mouseSpeed(mouseSpeed),
			att_isMouseIn(true), att_isMoving(false), att_jumpPos({0.7f, 0.6f, 0.5f, 0.4f, 0.3f}), att_currentJump(0) {}
		bool control(Vector3f &location, int width, int height, float speed, float gravity);
		void updateCamera(const Vector3f &location) const;
		void lookAt(float pitch, float yaw);
		float getPitch() const;
		float getYaw() const;
		Vector3f getSight() const; //From spherical coordinates (center + direction) to cartesian ones (x, y, z)
		bool isMouseIn() const {return att_isMouseIn;}
		bool &isMouseIn() {return att_isMouseIn;}
		bool isMoving();
		void jump();
		bool doesJump(Vector3f &location);
	};
}

#endif