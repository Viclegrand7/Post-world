#ifndef RV_ZD_IOSTREAM
#define RV_ZD_IOSTREAM
#include <iostream>
#endif



struct Vector3f { //All public, let's get it by default
	float att_x, att_y, att_z;//I truly want 3D. How? Rects won't do most likely?
//Should be with the Z buffer. SHould work with Rectangles, eventually
	Vector3f(float x = 0, float y = 0, float z = 0) : att_x(x), att_y(y), att_z(z) {}
	void print() {
		std :: cout << '(' <<  att_x << ", " << att_y << ", " << att_z << ")\n";
	}
};