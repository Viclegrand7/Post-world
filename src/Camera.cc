#ifndef RV_ZD_CAMERA_H
#define RV_ZD_CAMERA_H
#include "Camera.hh"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////
Uint8 UP_Key = SDL_SCANCODE_W; //Default seems to be WASD keyboard
Uint8 DOWN_Key = SDL_SCANCODE_S;
Uint8 LEFT_Key = SDL_SCANCODE_A;
Uint8 RIGHT_Key = SDL_SCANCODE_D;

Uint8 TILT_LEFT_Key = SDLK_a; 	//0 clue yet how to make camera move according to this number
Uint8 TILT_RIGHT_Key = SDLK_e;	//This one too
//Might be too lzay to use those tbh

//{...}
bool NO_GRAVITY(false); //If we cheat, it goes to true

///////////////////////////////////////////////////////////////////////////////////////////////
//Find better way to do it, should allow for modifying keys


//Private
void Camera :: lockCamera() {
	att_camPitch = att_camPitch > 89.0f ? 89.0f : (att_camPitch < -89.0f ? -89.0f : att_camPitch); //Stuck between -89 et 89. 90 degrees fuck up
	att_camYaw = att_camYaw < 0.0f ? att_camYaw + 360.0f : (att_camYaw > 360.0f ? att_camYaw - 360.0f : att_camYaw); //Stuck between 0 and 360°.
}

void Camera :: moveCamera(const float &dir) {
	float rad((att_camYaw + dir) * M_PI / 180);
	att_loc.att_x -= sin(rad) * att_speed;
	att_loc.att_y -= cos(rad) * att_speed;
}

void Camera :: moveCameraUp(const float &dir) {
	float rad((att_camPitch + dir) * M_PI / 180);
	att_loc.att_y += sin(rad) * att_speed;
}


//Public
void Camera :: control(const Render &window, bool isFullScreen) {
	if (att_mi)  {//If mouse is in the window, take it into account

///////////////////////////////////////////////////////////////////////////////////////////////
		int midX, midY;
		window.getSizes(midX, midY); //Need to find a way to provide the window OR the sizes
		midX /= 2;
		midY /= 2;
///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
		SDL_ShowCursor(SDL_DISABLE); //Should only use it when going out of setting and inside window actually
///////////////////////////////////////////////////////////////////////////////////////////////

		int tmpx, tmpy;
		SDL_GetMouseState(&tmpx, &tmpy);
		if (!isFullScreen)
			tmpy += 23;
		std :: cout << "MidX " << midX << " | tmpx " << tmpx << " | MidY " << midY << " | tmpy " << tmpy << std :: endl << getLoc();
		att_camYaw += att_mouseSpeed * (midX - tmpx);
		att_camPitch += att_mouseSpeed * (midY - tmpy);
		lockCamera();
		SDL_WarpMouseGlobal(midX, midY); 
		const Uint8 *state(SDL_GetKeyboardState(NULL)); //Gets all the keys' states (Is_Pressed ? 1 : 0). We can deal with what they do camera-wise
		if (state[UP_Key]) {
			moveCamera(0);
			if (NO_GRAVITY)
				moveCameraUp(0);
		}
		if (state[DOWN_Key]) {
			moveCamera(180);
			if (NO_GRAVITY)
				moveCameraUp(180);
		}
		if (state[LEFT_Key]) {
			moveCamera(90);
			if (NO_GRAVITY)
				moveCamera(90);
		}
		if (state[RIGHT_Key]) {
			moveCamera(270);
			if (NO_GRAVITY)
				moveCameraUp(270);
		}
	}
	glRotatef(-att_camPitch, 	1, 0, 0);
	glRotatef(-att_camYaw, 		0, 1, 0);	//In OPENGL, Y is up-down
	glRotatef(-att_camRoll, 	0, 0, 1); //I think?
}

void Camera :: updateCamera() {
	glTranslatef(- att_loc.att_x, - att_loc.att_y, - att_loc.att_z);
}

Vector3f Camera :: getLoc() {
	return att_loc;
}

Vector3f Camera :: getVec() const { //From spherical coordinates (center + direction) to cartesian ones (x, y, z)
	//Thank God I went through it with Chlamydomonas
	return Vector3f(- cos(att_camPitch * M_PI / 180) * sin (att_camYaw * M_PI / 180), sin(att_camPitch * M_PI / 180), - cos(att_camPitch * M_PI / 180) * cos(att_camYaw * M_PI / 180));
}

float Camera :: getPitch() const {
	return att_camPitch;
}

float Camera :: getYaw() const {
	return att_camYaw;
}

float Camera :: getRoll() const {
	return att_camRoll;
}

float Camera :: getSpeed() const {
	return att_speed;
}

float Camera :: getMouseSpeed() const {
	return att_mouseSpeed;
}

bool Camera :: isMouseIn() const {
	return att_mi;
}



void Camera :: setLocation(const Vector3f &vec) { //Move player
	att_loc = vec;
}

void Camera :: lookAt(const float &pitch, const float &yaw) { //Force camera movement
	att_camPitch = pitch;
	att_camYaw = yaw;
	att_camRoll = 0;
}

void Camera :: mouseIn(const bool &mi) {
	att_mi = mi;
}

void Camera :: setSpeed(const float &speed, const float &mouseSpeed) { //Sprint, moveHacks,...
	att_speed = speed;
	att_mouseSpeed = mouseSpeed;
}