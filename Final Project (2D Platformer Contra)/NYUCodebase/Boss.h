#ifndef BOSS_H
#define BOSS_H
#include "ShaderProgram.h"
#include "Vector3.h"
#include "Bullets.h"
#include "BigBullet.h"
#include <string>
#include "ParticleEmitter.h"
#pragma once

class Boss
{
public:
	enum EntityType { ENTITY_BOSS, ENTITY_COMPLEX, ENTITY_SIMPLE, ENTITY_BOX };
	Boss();
	void update(float elapsed);
	void render(ShaderProgram *program);
	bool square_collision_detect(float* R1_sides, float* R2_sides);
	void reset_collision_flags();
	void ShootMud(BigBullet& bullet, float elapsed);
	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);


	ParticleEmitter part;
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

	bool shoot;
	bool hide;
	bool bored;
	bool hurt;
	int health;

	const int deathAnimation[4] = { 12, 13, 14, 15 };
	const int deathNumFrames = 4;
	float deathAnimationElapsed = 0.0f;
	float deathFramesPerSecond = 4.0f;
	int deathCurrentIndex = 0;

	const int runAnimation[4] = { 28, 29, 30, 31 };
	const int NumFrames = 4;
	float AnimationElapsed = 0.0f;
	float FramesPerSecond = 4.0f;
	int CurrentIndex = 0;
};

#endif