#pragma once
#ifndef TEXT_H
#define TEXT_H

#pragma once
#include "Vector3.h"
#include "SheetSprite.h"
#include <vector>
#include "ShaderProgram.h"

class Text {

public:
	Text();
	void Identity();
	void DrawText(ShaderProgram *program, int fontTexture, std::string text, float size, float spacing);

	void SetRotation(float rotate);
	void SetPosition(float x, float y, float z);
	void SetSize(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void SetSpriteSheet(SheetSprite& sheet);
	void Draw(ShaderProgram *program, Matrix& model);

	Vector3 position;
	Vector3 velocity;
	Vector3 size;
	GLuint textureId;
	float rotation = 0.0f;
};
#endif