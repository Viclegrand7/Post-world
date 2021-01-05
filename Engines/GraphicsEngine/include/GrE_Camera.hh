#ifndef RV_ZD_GRECAMERA
#define RV_ZD_GRECAMERA

#include "Vector3f.hh"
#include <vector>

namespace Graphic {
	class Camera {
		Vector3f att_location;
		float att_pitch;
		float att_yaw;
		float att_roll;
		float att_mouseSpeed;
	
		bool att_isMouseIn;
		bool att_isMoving;

		void lockCamera();
		void moveCamera(float direction, float speed);
		void moveCameraUp(float direction, float speed);
		void handleMoves(float speed);
		std :: vector <float> att_jumpPos;
		unsigned int att_currentJump;
	public:
		Camera(const Vector3f &loc = Vector3f(0.0f, 0.0f, 5.0f), float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f, float mouseSpeed = 0.1f)
			: att_location(loc), att_pitch(pitch), att_yaw(yaw), att_roll(roll), att_mouseSpeed(mouseSpeed),
			att_isMouseIn(true), att_isMoving(false), att_jumpPos({0.7f, 0.6f, 0.5f, 0.4f, 0.3f}), att_currentJump(0) {}
		bool control(int width, int height, bool isFullScreen, float speed, float gravity);
		void updateCamera() const;
		void setLocation(const Vector3f &location);
		Vector3f &getLocation() {return att_location;}
		void lookAt(float pitch, float yaw);
		float getPitch() const;
		float getYaw() const;
		Vector3f getSight() const; //From spherical coordinates (center + direction) to cartesian ones (x, y, z)
		bool isMouseIn() const {return att_isMouseIn;}
		bool &isMouseIn() {return att_isMouseIn;}
		bool isMoving();
		void jump();
		bool doJump();
	};
}

#endif