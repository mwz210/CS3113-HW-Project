#include "Vector3.h"

Vector3::Vector3() { this->Identity(); }
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

void Vector3::Identity()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}