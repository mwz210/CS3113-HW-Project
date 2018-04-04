#include "Other.h"

Other::Other() {
	this->isStatic = false;
	this->entityType = ENTITY_Other;
	this->size.x = 1.0f;
	this->size.y = 1.0f;

	Vector3 topLeft;
	Vector3 topRight;
	Vector3 bottomLeft;
	Vector3 bottomRight;

	bottomLeft.x = -0.5f * this->size.x;
	bottomLeft.y = -0.5 * this->size.y;
	bottomRight.x = 0.5f * this->size.x;
	bottomRight.y = -0.5f * this->size.y;

	topLeft.x = -0.5f * this->size.x;
	topLeft.y = 0.5f * this->size.y;
	topRight.x = 0.5f * this->size.x;
	topRight.y = 0.5f * this->size.y;

	/*
	topLeft = topLeft * this->model;
	topRight = topRight * this->model;
	bottomLeft = bottomLeft * this->model;
	bottomRight = bottomRight * this->model;
	*/
	this->points.push_back(topLeft);
	this->points.push_back(topRight);
	this->points.push_back(bottomLeft);
	this->points.push_back(bottomRight);
}

void Other::reset_collision_flags() {
	this->collidedTop = false;
	this->collidedRight = false;
	this->collidedBottom = false;
	this->collidedLeft = false;
	this->isMoving = false;
}

void Other::update(float elapsed) {
	/*
	Vector3 topLeft;
	Vector3 topRight;
	Vector3 bottomLeft;
	Vector3 bottomRight;

	bottomLeft.x = -0.5f * this->size.x;
	bottomLeft.y = -0.5 * this->size.y;
	bottomRight.x = 0.5f * this->size.x;
	bottomRight.y = -0.5f * this->size.y;

	topLeft.x = -0.5f * this->size.x;
	topLeft.y = 0.5f * this->size.y;
	topRight.x = 0.5f * this->size.x;
	topRight.y = 0.5f * this->size.y;

	topLeft = topLeft * this->model;
	topRight = topRight * this->model;
	bottomLeft = bottomLeft * this->model;
	bottomRight = bottomRight * this->model;

	this->points[0] = topLeft;
	this->points[1] = topRight;
	this->points[2] = bottomLeft;
	this->points[3] = bottomRight;
	*/

	const Uint8 *key = SDL_GetKeyboardState(NULL);

	this->model.SetPosition(this->position.x, this->position.y, 0);
	// moving on x
}

void Other::render(ShaderProgram* program) {
	program->SetModelMatrix(this->model);
	this->DrawSpriteSheetSprite(*program, 157, 16, 8);
}

bool Other::square_collision_detect(float* R1_sides, float* R2_sides)
{
	return(!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}

void Other::DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
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