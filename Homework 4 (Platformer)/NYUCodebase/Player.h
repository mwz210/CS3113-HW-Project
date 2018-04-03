#ifndef PLAYER_H
#define PLAYER_H
#include "ShaderProgram.h"
#include "Vector3.h"
#include <math.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Bullets.h"
#pragma once

class Player
{
public: 
	enum EntityType { ENTITY_PLAYER, ENTITY_ENEMY, ENTITY_BULLET };
	Player();
	void update(float elapsed);
	void render(ShaderProgram *program, Matrix& model, const int runAnimation[], int currentIndex);
	bool square_collision_detect(float* R1_sides, float* R2_sides);
	void reset_collision_flags();
	void ShootBullets(Bullets& bullet, float elapsed);

	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 acceleration;

	bool isMoving;
	bool isStatic;
	bool exist;
	EntityType entityType;

	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
};

#endif PLAYER_H

