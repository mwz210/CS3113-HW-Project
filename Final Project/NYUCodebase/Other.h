#ifndef Other_H
#define Other_H
#define PI 3.14159265358979323846264338328
#include "ShaderProgram.h"
#include "Vector3.h"
#include <math.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>

#pragma once

class Other
{
public:
	enum EntityType { ENTITY_Other, ENTITY_ENEMY, ENTITY_BULLET };
	Other();
	void update(float elapsed);
	void render(ShaderProgram *program);
	bool square_collision_detect(float* R1_sides, float* R2_sides);
	void reset_collision_flags();

	Matrix model;
	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 acceleration;

	bool isMoving;
	bool isStatic;
	bool exist;
	EntityType entityType;

	std::vector<Vector3> points;

	void DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
};

#endif Other_H

#pragma once
