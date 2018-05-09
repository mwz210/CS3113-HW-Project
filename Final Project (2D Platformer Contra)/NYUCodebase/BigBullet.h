#pragma once
#ifndef BIGBULLET_H
#define BIGBULLET_H

#include "ShaderProgram.h"
#include "Matrix.h"
#include "Vector3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <string>
#include "ParticleEmitter.h"

class BigBullet
{
public:
	BigBullet();
	void update(float elapsed, Vector3& position, Vector3& size, bool shoot, bool direction);
	void update(float elapsed, Vector3& position, Vector3& other_size);
	void update(float elapsed);

	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	void Identity();

	void SetRotation(float rotate);
	void SetPosition(float x, float y, float z);
	void SetSize(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void Drawful(ShaderProgram *program);

	void ChangeModel(Matrix& model);

	Vector3 position;
	Vector3 velocity;
	Vector3 size;
	
	ParticleEmitter emit;

	bool directionShot;
	float sides[4];

	float rotation = 0.0f;

	bool isMoving;
	bool isStatic;
	bool hit;
	float limit;
};

#endif
