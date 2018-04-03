#include "Ground.h"

Ground::Ground() {
	this->isStatic = true;
}

void Ground::DrawSpriteSheetSprite(ShaderProgram& program,int index, int spriteCountX, int spriteCountY, float size) {
	if (index != 0)
	{
		float u = (float)((int)index % spriteCountX) / (float)spriteCountX;
		float v = (float)((int)index / spriteCountX) / (float)spriteCountY;
		float spriteWidth = 1.0 / (float)spriteCountX;
		float spriteHeight = 1.0 / (float)spriteCountY;
		float aspect = 256.0 / 128.0;

		float vertices[] = {
			-0.5f * size, -0.5f * size,
			0.5f * size, 0.5 * size,
			-0.5f * size, 0.5f * size,
			0.5f * size, 0.5f * size,
			-0.5f * size, -0.5f * size,
			0.5f * size, -0.5f * size };

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