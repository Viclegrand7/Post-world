#ifndef RV_ZD_VECT3F
#define RV_ZD_VECT3F

#include <iostream>

struct Vector3f { //Everything will be public, will be easier to work with it
	float att_x;
	float att_y;
	float att_z;

	Vector3f(float x = 0, float y = 0, float z = 0) : att_x(x), att_y(y), att_z(z) {}
	Vector3f(const Vector3f &other) : att_x(other.att_x), att_y(other.att_y), att_z(other.att_z) {}

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

#endif