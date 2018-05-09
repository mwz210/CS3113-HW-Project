#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <vector>
#include "Particle.h"
#include "Vector3.h"
#include "Color.h"
#include "ShaderProgram.h"	
class ParticleEmitter {
	public:
		ParticleEmitter(unsigned int particleCount);
		ParticleEmitter();
		~ParticleEmitter();

		void Update(float elapsed);
		void Render(ShaderProgram& program, int index);

		Vector3 position;
		Vector3 gravity;
		float maxLifetime;
		Vector3 velocity;
		Vector3 velocityDeviation;
		Color startColor;
		Color endColor;
		float startSize;
		float endSize;
		float sizeDeviation;
		float index;
		float perlinValue;
		bool reset;
		bool random;

		std::vector<Particle*> particles;

		void ParticleEmitter::DrawSpriteSheetSprite(ShaderProgram* program, int index, int spriteCountX, int spriteCountY);


};

#endif 