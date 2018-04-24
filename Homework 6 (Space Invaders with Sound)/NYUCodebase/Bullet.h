#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"
#include "SheetSprite.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class Bullet
{
	public:
		Bullet();
		void update(float elapsed, Vector3& position, Vector3& size, bool shoot);
		void update(float elapsed, Vector3& position, Vector3& other_size);
		void update(float elapsed);
		void Identity();

		void SetRotation(float rotate);
		void SetPosition(float x, float y, float z);
		void SetSize(float x, float y, float z);
		void SetVelocity(float x, float y, float z);
		void SetSpriteSheet(SheetSprite& sheet);
		void Draw(ShaderProgram *program, Matrix& model);

		void ChangeModel(Matrix& model);

		Vector3 position;
		Vector3 velocity;
		Vector3 size;
		bool exist;
		float sides[4];

		float rotation = 0.0f;
		SheetSprite sheet;
};

#endif 
