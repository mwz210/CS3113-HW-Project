#pragma once
#ifndef COIN_H
#define COIN_H

#include "ShaderProgram.h"
#include "Matrix.h"
#include "Vector3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class Coin {
	public:
		Coin();
		void update(float elapsed);
		void DrawSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

		void Render(ShaderProgram *program, const int runAnimation[], int currentIndex);
		

		Vector3 position;
		Vector3 velocity;
		Vector3 size;

		bool exist;
		float sides[4];
		

};


#endif // !COIN_H
