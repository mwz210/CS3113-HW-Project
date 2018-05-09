#include "ParticleEmitter.h"
#include "PerlinNoise.h"

float lerp(float v0, float v1, float t) {
	return (1.0 - t) * v0 + t * v1;
}

void ParticleEmitter::Update(float elapsed) {
	this->perlinValue += elapsed;
	for (int i = 0; i < particles.size(); i++) {
		float coord[2] = { perlinValue, this->particles[i]->perlinY };
		this->particles[i]->position.x += noise2(coord) * .03f;
		coord[0] = perlinValue * 0.5f;
		this->particles[i]->position.y += noise2(coord) * .03f;
		this->particles[i]->velocity.y += this->gravity.y * elapsed;
		this->particles[i]->position.y += this->particles[i]->velocity.y * elapsed;
		this->particles[i]->position.x += this->particles[i]->velocity.x * elapsed;
		this->particles[i]->lifetime -= elapsed;
		if (this->particles[i]->lifetime <= 0 && this->reset == true) {
			this->particles[i]->position.x = this->position.x;
			this->particles[i]->position.y = this->position.y;
			this->particles[i]->lifetime = ((float)rand() / RAND_MAX) * this->maxLifetime;
			this->particles[i]->velocity.y = this->velocity.y;
			int sign = rand() % 2;
			if (sign == 1) {
				this->particles[i]->velocity.x = ((float)rand() / RAND_MAX) * this->velocity.x;
			}
			else {
				this->particles[i]->velocity.x = ((float)rand() / RAND_MAX) * -this->velocity.x;
			}
		}
	}
}

ParticleEmitter::ParticleEmitter(unsigned int particleCount) {
	this->velocity.y = 0.2f;
	this->velocity.x = 1.0f;
	this->maxLifetime = 2.0f;
	this->gravity.y = -1.0f;
	this->startSize = 0.2f;
	this->endSize = 0.0f;
	this->sizeDeviation = 0.1f;
	this->reset = true;
	for (int i = 0; i < particleCount; i++) {
		Particle* part = new Particle;
		part->lifetime = ((float)rand() / RAND_MAX) * this->maxLifetime;
		part->perlinY = rand();
		part->position.x = this->position.x;
		part->position.y = this->position.y;
		part->sizeDeviation = this->sizeDeviation;
		this->particles.push_back(part);
	}
}

ParticleEmitter::ParticleEmitter() {
	this->velocity.y = 0.2f;
	this->velocity.x = 1.0f;
	this->maxLifetime = 2.0f;
	this->gravity.y = -1.0f;
	this->startSize = 0.2f;
	this->endSize = 0.0f;
	this->sizeDeviation = 0.1f;
	this->reset = true;
	for (int i = 0; i < 25; i++) {
		Particle* part = new Particle;
		part->lifetime = ((float)rand() / RAND_MAX) * this->maxLifetime;
		part->perlinY = rand();
		part->position.x = this->position.x;
		part->position.y = this->position.y;
		part->sizeDeviation = this->sizeDeviation;
		this->particles.push_back(part);
	}
}

void ParticleEmitter::Render(ShaderProgram& program, int index) {
	Matrix modelMatrix;
	modelMatrix.SetPosition(this->position.x, this->position.y, 0.0f);
	program.SetModelMatrix(modelMatrix);
	DrawSpriteSheetSprite(&program, index, 16, 8);
}

ParticleEmitter::~ParticleEmitter() {
	for (int i = 0; i < this->particles.size(); i++) {
		delete this->particles[i];
	}
	this->particles.clear();
}

void ParticleEmitter::DrawSpriteSheetSprite(ShaderProgram* program, int index, int spriteCountX, int spriteCountY) {
	if (index != 0)
	{
		if (this->random == true) {
			index += rand() % 4;
		}
		float u = (float)((int)index % spriteCountX) / (float)spriteCountX;
		float v = (float)((int)index / spriteCountX) / (float)spriteCountY;
		float spriteWidth = 1.0 / (float)spriteCountX;
		float spriteHeight = 1.0 / (float)spriteCountY;
		float aspect = 256.0 / 128.0;

		std::vector<float> vertices;
		std::vector<float> texCoords;

		for (int i = 0; i < this->particles.size(); i++) {
			if (this->particles[i]->lifetime > 0 && this->reset == false) {
				float m = (this->particles[i]->lifetime / this->maxLifetime);
				float size = lerp(this->startSize, this->endSize, m) + this->particles[i]->sizeDeviation;

				vertices.insert(vertices.end(), {
					this->particles[i]->position.x - size, this->particles[i]->position.y - size,
					this->particles[i]->position.x + size, this->particles[i]->position.y + size,
					this->particles[i]->position.x - size, this->particles[i]->position.y + size,

					this->particles[i]->position.x + size, this->particles[i]->position.y + size,
					this->particles[i]->position.x - size, this->particles[i]->position.y - size,
					particles[i]->position.x + size, this->particles[i]->position.y - size,
					});

				texCoords.insert(texCoords.end(), {
					u, v + spriteHeight,
					u + spriteWidth, v,
					u, v,
					u + spriteWidth, v,
					u, v + spriteHeight,
					u + spriteWidth, v + spriteHeight
					});
			}
			glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
			glEnableVertexAttribArray(program->positionAttribute);
			glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
			glEnableVertexAttribArray(program->texCoordAttribute);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 2);
			}
	}
}