#include "Enemy.h"

Enemy::Enemy() {
	this->isStatic = false;
	this->entityType = ENTITY_ENEMY;
	this->size.x = 2.0f;
	this->size.y = 2.0f;
	this->acceleration.y = -0.5;
	this->health = 100;
}

void Enemy::reset_collision_flags() {
	this->collidedTop = false;
	this->collidedRight = false;
	this->collidedBottom = false;
	this->collidedLeft = false;
}

void Enemy::ShootMud(Bullets& bullet, float elapsed) {
	bullet.update(elapsed, this->position, this->size, true);
}

void Enemy::update(float elapsed) {
	const Uint8 *key = SDL_GetKeyboardState(NULL);

	if (this->collidedBottom == false) {
		this->acceleration.y = -1.0;
		this->velocity.y += this->acceleration.y * elapsed;
		this->position.y += this->velocity.y * elapsed;
	}
	this->position.y += this->velocity.y * elapsed;
}

void Enemy::render(ShaderProgram* program, Matrix& model) {
	model.SetPosition(this->position.x, this->position.y, 0);
	program->SetModelMatrix(model);
	if (this->health > 0){ this->DrawSpriteSheetSprite(*program, 102, 16, 8); }
}

bool Enemy::square_collision_detect(float* R1_sides, float* R2_sides)
{
	return(!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}

void Enemy::DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
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