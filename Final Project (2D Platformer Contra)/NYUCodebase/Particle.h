#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"

class Particle {
	public:
		Particle();
		Vector3 position;
		Vector3 velocity;
		float lifetime;
		float sizeDeviation;
		float rotation;
		float perlinY;
};

#endif 
