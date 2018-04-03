#pragma once
#ifndef BULLETS_H
#define BULLETS_H

#include "ShaderProgram.h"
#include "Matrix.h"
#include "Vector3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class Bullets
{
public:
	enum EntityType { ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET };
	Bullets();
	void update(float elapsed, Vector3& position, Vector3& size, bool shoot);
	void update(float elapsed, Vector3& position, Vector3& other_size);
	void update(float elapsed);

	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	void Identity();

	void SetRotation(float rotate);
	void SetPosition(float x, float y, float z);
	void SetSize(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void Draw(ShaderProgram *program, Matrix& model);

	void ChangeModel(Matrix& model);

	Vector3 position;
	Vector3 velocity;
	Vector3 size;
	
	float sides[4];

	float rotation = 0.0f;

	bool isMoving;
	bool isStatic;
	bool hit;
	EntityType entityType;
};

#endif
