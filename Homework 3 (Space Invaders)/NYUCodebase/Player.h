#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SheetSprite.h"
#include "Vector3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Bullet.h"

class Player
{
public:
	Player();
	void update(float elapsed);
	
	void Identity();

	void SetRotation(float rotate);
	void SetPosition(float x, float y, float z);
	void SetSize(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void SetSpriteSheet(SheetSprite sheet);

	void Draw(ShaderProgram *program, Matrix& model);

	void ChangeModel(Matrix& model);
	void ShootBullets(Bullet& pellet, float elapsed);
	Vector3 position;
	Vector3 velocity;
	Vector3 size;
	bool exist;
	float sides[4];

	float rotation = 0.0f;

	SheetSprite sprite;
};

#endif