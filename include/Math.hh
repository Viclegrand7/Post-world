#ifndef RV_ZD_IOSTREAM
#define RV_ZD_IOSTREAM
#include <iostream>
#endif

#ifndef RV_ZD_CMATH
#define RV_ZD_CMATH
#include <cmath>
#endif


struct Vector3f { //All public, let's get it by default
	float att_x, att_y, att_z;//I truly want 3D. How? Rects won't do most likely?
//Should be with the Z buffer. SHould work with Rectangles, eventually
	Vector3f(float x = 0, float y = 0, float z = 0) : att_x(x), att_y(y), att_z(z) {}
	void print() {
		std :: cout << '(' <<  att_x << ", " << att_y << ", " << att_z << ")\n";
	}
	float dotProduct(const Vector3f &other) const;
	Vector3f crossProduct(const Vector3f &other) const;
	float length() const;
	void normalize();

	Vector3f &operator=(const Vector3f &other);
	
	Vector3f operator+(const Vector3f &other) const;
	Vector3f operator-(const Vector3f &other) const;
	Vector3f operator*(const float &value) const;
	friend Vector3f operator*(const float &value, const Vector3f &vect);
	Vector3f operator/(const float &value) const;
	friend Vector3f operator/(const float &value, const Vector3f &vect);

	Vector3f &operator+=(const Vector3f &other);
	Vector3f &operator-=(const Vector3f &other);
	Vector3f &operator*=(const float &value);
	Vector3f &operator/=(const float &value);

	bool operator==(const Vector3f &other) const;
	bool operator!=(const Vector3f &other) const;

	Vector3f operator-() const;

	friend std :: ostream &operator<<(std :: ostream &out, const Vector3f &someone);
};
