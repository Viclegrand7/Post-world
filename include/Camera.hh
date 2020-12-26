#ifndef RV_ZD_MATH_H
#define RV_ZD_MATH_H
#include "Math.hh"
#endif
//Gonna be using Vector3f

#ifndef RV_ZD_CMATH
#define RV_ZD_CMATH
#include <cmath>
#endif

#ifndef RV_ZD_SDL_H
#define RV_ZD_SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef RV_ZD_Render_H
#define RV_ZD_RENDER_H
#include "Render.hh"
#endif

#ifndef RV_ZD_GL_H
#define RV_ZD_GL_H
#include <GL/gl.h>
#endif

#ifndef RV_ZD_GLU_H
#define RV_ZD_GLU_H
#include <GL/glu.h>
#endif




class Camera {
	Vector3f att_loc;
	float att_camPitch, att_camYaw, att_camRoll; //Yaw = left-right, around Y-axis. Pitch = Up-down, around X-axis. Roll = tilting head, around Z-axis
	//Might be too lazy to tilt head tbh
	float att_speed, att_mouseSpeed; //movevel, mousevel
	bool att_mi, att_isMoving; //Inside window or not, moving head or not
	
	void lockCamera();
	void moveCamera(const float &dir);
	void moveCameraUp(const float &dir);

public:
	Camera(const Vector3f &loc = Vector3f(0,0,0), const float &pitch = 0, const float &yaw = 0, const float &moveVelo = 0.2, const float &mouseVelo = 0.2)
	: att_loc(loc), att_camPitch(pitch), att_camYaw(yaw), att_speed(moveVelo), att_mouseSpeed(mouseVelo), att_mi(true), att_isMoving(false) {}

	void control(const Render &, bool);
	void updateCamera();
	Vector3f getLoc();
	Vector3f getVec() const; //From spherical coordinates (center + direction) to cartesian ones (x, y, z)
	float getPitch() const;
	float getYaw() const;
	float getRoll() const;
	float getSpeed() const;
	float getMouseSpeed() const;
	bool isMouseIn() const;
	bool isMoving() const;

	void setLocation(const Vector3f &vec); //Move player
	void lookAt(const float &pitch, const float &yaw); //Force camera movement
	void mouseIn(const bool &mi);
	void setSpeed(const float &speed, const float &mouseSpeed); //Sprint, moveHacks,...
};