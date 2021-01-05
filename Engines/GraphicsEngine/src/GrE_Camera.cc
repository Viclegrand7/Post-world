#include "GrE_Camera.hh"

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <cmath>

Uint8 UP_Key = SDL_SCANCODE_W; //Default seems to be WASD keyboard
Uint8 DOWN_Key = SDL_SCANCODE_S;
Uint8 LEFT_Key = SDL_SCANCODE_A;
Uint8 RIGHT_Key = SDL_SCANCODE_D;

void Graphic :: Camera :: lockCamera() {
	att_pitch = att_pitch > 89.0f ? 89.0f : (att_pitch < -89.0f ? -89.0f : att_pitch); //Stuck between -89 et 89. 90 degrees fuck up (Chlamydomonas)
	att_yaw = att_yaw < 0.0f ? att_yaw + 360.0f : (att_yaw > 360.0f ? att_yaw - 360.0f : att_yaw); //Stuck between 0 and 360°.
	att_roll = att_roll < -3.0f ? -3.0f : (att_roll > 3.0f ? 3.0f : att_roll);
}

void Graphic :: Camera :: moveCamera(float direction, float speed) {
	float rad((att_yaw + direction) * M_PI / 180.0f); //Don't ask me, ask the Internet
	att_location.att_x -= sin(rad) * speed;
	att_location.att_z -= cos(rad) * speed;
}

void Graphic :: Camera :: moveCameraUp(float direction, float speed) {
	float rad((att_pitch + direction) * M_PI / 180.0f);
	att_location.att_y += sin(rad) * speed;
}

void Graphic :: Camera :: handleMoves(float speed) {
	att_isMoving = false;
	const Uint8 *keyboardState(SDL_GetKeyboardState(NULL)); //Gets all the keys' states (Is_Pressed ? 1 : 0). We can deal with what they do camera-wise
	if (keyboardState[UP_Key]) {
		if (!keyboardState[DOWN_Key])
			att_isMoving = true;
		moveCamera(0, speed);
//		if (NO_GRAVITY)
			moveCameraUp(0, speed);
	}
	if (keyboardState[DOWN_Key]) {
		if (!keyboardState[UP_Key])
			att_isMoving = true;
		moveCamera(180, speed);
//		if (NO_GRAVITY)
			moveCameraUp(180, speed);
	}
	if (keyboardState[LEFT_Key]) {
		if (!keyboardState[RIGHT_Key])
			att_isMoving = true;
		moveCamera(90, speed);
	}
	if (keyboardState[RIGHT_Key]) {
		if (!keyboardState[LEFT_Key])
			att_isMoving = true;
		moveCamera(270, speed);
	}
}

bool Graphic :: Camera :: control(int width, int height, bool isFullScreen, float speed, float gravity) {
	if (att_isMouseIn) { //Is no when alt tabbed, when in settings,...
		width /= 2 ; height /= 2 ; //Get middle of screen
		int tmpx, tmpy;
		SDL_GetMouseState(&tmpx, &tmpy);
		if (!isFullScreen)
			tmpy += 23; //Seems like the top border is 46 pixels high or something. Worked for me

		att_yaw += att_mouseSpeed * (width - tmpx);
		att_pitch += att_mouseSpeed * (height - tmpy);
		SDL_WarpMouseGlobal(width, height);
		lockCamera();

		handleMoves(speed); //deals with Keyboard
	}
	glRotatef(-att_pitch,	1, 0, 0);
	glRotatef(-att_yaw,		0, 1, 0); //In OPENGL, Y is up-down axis
//	glRotatef(-att_roll,	0, 0, 1); //Never saw that, DOES NOT WORK. TILTS IN ABSOLUTE (doesn't consider where we look at)
	att_location.att_y -= gravity;
	return doJump();
}

void Graphic :: Camera :: updateCamera() const {
	glTranslatef(-att_location.att_x, -att_location.att_y, -att_location.att_z);
}

void Graphic :: Camera :: setLocation(const Vector3f &location) {
	att_location = location;
}

void Graphic :: Camera :: lookAt(float pitch, float yaw) {
	att_pitch = pitch;
	att_yaw = yaw;
	att_roll = 0;
}

float Graphic :: Camera :: getPitch() const {
	return att_pitch;
}

float Graphic :: Camera :: getYaw() const {
	return att_yaw;
}

Vector3f Graphic :: Camera :: getSight() const { //From spherical coordinates (center + direction) to cartesian ones (x, y, z)
	//Thank God I went through it with Chlamydomonas
	return Vector3f(- cos(att_pitch * M_PI / 180) * sin (att_yaw * M_PI / 180), sin(att_pitch * M_PI / 180), - cos(att_pitch * M_PI / 180) * cos(att_yaw * M_PI / 180));
}

bool Graphic :: Camera :: isMoving() {
	return att_isMoving;
}

void Graphic :: Camera :: jump() {
	att_currentJump = 1;
}

bool Graphic :: Camera :: doJump() {
	if (att_currentJump) {
		att_location.att_y += att_jumpPos[att_currentJump - 1];
		if (++att_currentJump > att_jumpPos.size()) {
			att_currentJump = 0;
			return true;
		}
	}
	return false;
}