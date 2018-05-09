#ifndef GROUND_H
#define GROUND_H
#include "ShaderProgram.h"
#include "Vector3.h"
#pragma once

class Ground
{
public:
	enum EntityType { ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET };
	Ground();
	void update(float elapsed);
	void render(ShaderProgram *program);
	bool collidesWith();

	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 acceleration;

	bool isStatic;
	EntityType entityType;
	int mapData;

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;

	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY, float size);
};

#endif GROUND_H
