#pragma once
#ifndef BOUNCE_H
#define BOUNCE_H

#include "ShaderProgram.h"
#include "Matrix.h"
#include "Vector3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class Bounce {
public:
	Bounce();
	void update(float elapsed);
	void DrawSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY);

	void Render(ShaderProgram *program);


	Vector3 position;
	Vector3 velocity;
	Vector3 size;

	float sides[4];
	bool step;

	const int runAnimation[2] = { 84, 85 };
	const int numFrames = 2;
	float animationElapsed = 0.0f;
	float framesPerSecond = 10.0f;
	int currentIndex = 0;

};


#endif // !COIN_H
