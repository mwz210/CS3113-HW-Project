#ifndef ENEMY_H
#define ENEMY_H
#include "ShaderProgram.h"
#include "Vector3.h"
#include "Bullets.h"
#include <string>
#include "ParticleEmitter.h"
#pragma once

class Enemy
{
public:
	enum EntityType { ENTITY_BOSS, ENTITY_COMPLEX, ENTITY_SIMPLE, ENTITY_BOX };
	Enemy();
	void update(float elapsed);
	void render(ShaderProgram *program);
	bool square_collision_detect(float* R1_sides, float* R2_sides);
	void reset_collision_flags();
	void ShootMud(Bullets& bullet, float elapsed);
	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 acceleration;

	float death;
	bool isStatic;
	bool exist;
	bool isMoving;
	bool direction;
	EntityType entityType;

	float farRightSide[2];
	float farLeftSide[2];
	float rightSide[2];
	float leftSide[2];

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;

	const int runAnimation[2] = { 80, 81 };
	const int numFrames = 2;
	float animationElapsed = 0.0f;
	float framesPerSecond = 5.0f;
	int currentIndex = 0;

	const int deathAnimation[5] = { 40, 41, 42, 43, 44 };
	const int deathNumFrames = 5;
	float deathAnimationElapsed = 0.0f;
	float deathFramesPerSecond = 5.0f;
	int deathCurrentIndex = 0;
};

#endif Enemy_H
