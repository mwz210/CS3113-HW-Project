#include "Vector3.h"

Vector3::Vector3() { this->Identity(); }
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

void Vector3::Identity()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

float Vector3::Length() {
	// 2D Magnitude 
	float x = this->x * this->x;
	float y = this->y * this->y;
	return (sqrtf(x + y));
}

void Vector3::Normalize() {
	// 2D Normalizing
	if (this->Length() != 0) {
		this->x /= this->Length();
		this->y /= this->Length();
	}
}

Vector3 Vector3::operator*(const Matrix& m) {
	float x = (m.m[0][0] * this->x) + (m.m[1][0] * this->y) + (m.m[2][0] * this->z) + (m.m[3][0] * 1);
	float y = (m.m[0][1] * this->x) + (m.m[1][1] * this->y) + (m.m[2][1] * this->z) + (m.m[3][1] * 1);
	float z = (m.m[0][2] * this->x) + (m.m[1][2] * this->y) + (m.m[2][2] * this->z) + (m.m[3][2] * 1);
	return Vector3(x, y, z);
}