#ifndef ENEMY_H
#define ENEMY_H
#include "ShaderProgram.h"
#include "Vector3.h"
#include "Bullets.h"
#pragma once



class Enemy
{
public:
	int health;

	enum EntityType { ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET };
	Enemy();
	void update(float elapsed);
	void render(ShaderProgram *program, Matrix& matrix);
	bool square_collision_detect(float* R1_sides, float* R2_sides);
	void reset_collision_flags();
	void ShootMud(Bullets& bullet, float elapsed);
	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 acceleration;

	bool isStatic;
	EntityType entityType;

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
};

#endif Enemy_H
