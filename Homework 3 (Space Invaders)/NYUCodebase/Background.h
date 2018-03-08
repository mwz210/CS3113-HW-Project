#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Vector3.h"
#include "SheetSprite.h"
#include <vector>
class Background {

public:
	Background();

	void SetSpriteSheet(SheetSprite sheet);
	void Draw(ShaderProgram *program, Matrix& model);

	Vector3 position;
	Vector3 velocity;
	Vector3 size;
	SheetSprite sprite;
	GLuint textureId;
	float rotation = 0.0f;
};

#endif