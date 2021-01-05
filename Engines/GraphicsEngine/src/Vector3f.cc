#include "Vector3f.hh"
#include <cmath>

float Vector3f :: dotProduct(const Vector3f &other) const {
	return att_x * other.att_x + att_y * other.att_y + att_z * other.att_z;
}

Vector3f Vector3f :: crossProduct(const Vector3f &other) const {
	return (Vector3f(att_y * other.att_z - att_z * other.att_y, att_x * other.att_z - att_z * other.att_x, att_x * other.att_y - att_y * other.att_x));
}

float Vector3f :: length() const {
	return sqrt(att_x * att_x + att_y * att_y + att_z * att_z);
}

void Vector3f :: normalize() {
	float temp(length());
	if (temp && temp != 1) {
		att_x /= temp;
		att_y /= temp;
		att_z /= temp;
	}
}

Vector3f &Vector3f :: operator=(const Vector3f &other) {
	att_x = other.att_x;
	att_y = other.att_y;
	att_z = other.att_z;
	return *this;
}

Vector3f Vector3f :: operator+(const Vector3f &other) const {
	return Vector3f(att_x + other.att_x, att_y + other.att_y, att_z + other.att_z);
}

Vector3f Vector3f :: operator-(const Vector3f &other) const {
	return Vector3f(att_x - other.att_x, att_y - other.att_y, att_z - other.att_z);
}

Vector3f Vector3f :: operator*(const float &value) const {
	return Vector3f(att_x * value, att_y * value, att_z * value);
}

Vector3f operator*(const float &value, const Vector3f &vect) {
	return Vector3f(vect.att_x * value, vect.att_y * value, vect.att_z * value);
}


Vector3f Vector3f :: operator/(const float &value) const {
	if (value)
		return Vector3f(att_x / value, att_y / value, att_z / value);
	return Vector3f(0,0,0); //error
}

Vector3f operator/(const float &value, const Vector3f &vect) {
	if (value)
		return Vector3f(vect.att_x / value, vect.att_y / value, vect.att_z / value);
	return Vector3f(0,0,0); //error	
}

Vector3f &Vector3f :: operator+=(const Vector3f &other) {
	att_x += other.att_x;
	att_y += other.att_y;
	att_z += other.att_z;
	return *this;
}

Vector3f &Vector3f :: operator-=(const Vector3f &other) {
	att_x -= other.att_x;
	att_y -= other.att_y;
	att_z -= other.att_z;
	return *this;
}

Vector3f &Vector3f :: operator*=(const float &value) {
	att_x *= value;
	att_y *= value;
	att_z *= value;
	return *this;
}

Vector3f &Vector3f :: operator/=(const float &value) {
	if (value) {
		att_x /= value;
		att_y /= value;
		att_z /= value;
	}
	return *this;
}

bool Vector3f :: operator==(const Vector3f &other) const {
	return (att_x == other.att_x && att_y == other.att_y && att_z == other.att_z);
}

bool Vector3f :: operator!=(const Vector3f &other) const {
	return !(*this == other);
}

Vector3f Vector3f :: operator-() const { //negative
	return Vector3f(-att_x, -att_y, -att_z);
}


std :: ostream &operator<<(std :: ostream &out, const Vector3f &someone) {
	out << "(" << someone.att_x << ", " << someone.att_y << ", " << someone.att_z << ")   ";
	return out;
}