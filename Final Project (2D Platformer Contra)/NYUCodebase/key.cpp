#include "key.h"

Key::Key() {
	this->size.x = .3;
	this->size.y = .3;
	this->exist = true;
}

void Key::Render(ShaderProgram *program) {
	Matrix modelMatrix;
	modelMatrix.SetPosition(this->position.x, this->position.y, 0.0);
	program->SetModelMatrix(modelMatrix);
	if (this->exist == true) {
		this->DrawSprite(*program, 86, 16, 8);
	}
	else {
		this->position.y = -300.0f;
	}
}

void Key::DrawSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
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