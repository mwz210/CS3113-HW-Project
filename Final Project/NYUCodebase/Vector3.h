#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include "Matrix.h"
class Vector3
{
public:
	Vector3(float x, float y, float z);
	Vector3();
	float x;
	float y;
	float z;
	Vector3 operator*(const Matrix& m);

	void Identity();
	float Length();
	void Normalize();
};

#endif
