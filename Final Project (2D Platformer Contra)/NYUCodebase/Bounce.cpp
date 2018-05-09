#include "Bounce.h"

Bounce::Bounce() {
	this->size.x = .3;
	this->size.y = .3;
	this->step = false;
}

void Bounce::update(float elapsed) {
	this->animationElapsed += elapsed;
	if (this->animationElapsed > 1.0 / this->framesPerSecond) {
		this->currentIndex++;
		this->animationElapsed = 0.0;
		if (this->currentIndex > this->numFrames - 1) {
			this->currentIndex = 0;
		}
	}
}

void Bounce::Render(ShaderProgram *program) {
	Matrix modelMatrix;
	modelMatrix.SetPosition(this->position.x, this->position.y, 0.0);
	program->SetModelMatrix(modelMatrix);
	if (this->step == true) {
		this->DrawSprite(*program, 85, 16, 8);
		this->step = false;
	}
	else {
		this->DrawSprite(*program, 84, 16, 8);
	}
}

void Bounce::DrawSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
	if (index != 0)
	{
		float u = (float)((int)index % spriteCountX) / (float)spriteCountX;
		float v = (float)((int)index / spriteCountX) / (float)spriteCountY;
		float spriteWidth = 1.0 / (float)spriteCountX;
		float spriteHeight = 1.0 / (float)spriteCountY;
		float aspect = 256.0 / 128.0;

		float vertices[] = {
			-0.5f * this->size.x, -0.5f * this->size.x,
			0.5f * this->size.x, 0.5 * this->size.x,
			-0.5f * this->size.x, 0.5f * this->size.x,
			0.5f * this->size.x, 0.5f * this->size.x,
			-0.5f * this->size.x, -0.5f * this->size.x,
			0.5f * this->size.x, -0.5f * this->size.x };

		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program.positionAttribute);

		float texCoords[] = {
			u, v + spriteHeight,
			u + spriteWidth, v,
			u, v,
			u + spriteWidth, v,
			u, v + spriteHeight,
			u + spriteWidth, v + spriteHeight
		};
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}