#pragma once

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
	public:
		Vector3(float x, float y, float z);
		Vector3();
		float x;
		float y;
		float z;

		void Identity();
};

#endif