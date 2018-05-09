#include "Enemy.h"

Enemy::Enemy() {
	this->isStatic = false;
	this->size.x = 0.3f;
	this->size.y = 0.3f;
	this->velocity.x = .5f;
	this->exist = true;
	this->direction = true;
	this->death = 1.0f;
}

void Enemy::reset_collision_flags() {
	this->collidedTop = false;
	this->collidedRight = false;
	this->collidedBottom = false;
	this->collidedLeft = false;
}

void Enemy::ShootMud(Bullets& bullet, float elapsed) {
	bullet.update(elapsed, this->position, this->size, true, "what");
}

void Enemy::update(float elapsed) {
	if (this->exist == false) {
		this->death -= elapsed;
	}
	const Uint8 *key = SDL_GetKeyboardState(NULL);
	this->rightSide[1] = this->position.y;
	this->rightSide[0] = this->position.x + .15f;
	this->leftSide[1] = this->position.y;
	this->leftSide[0] = this->position.x - .15f;
	this->farLeftSide[1] = this->position.y - 0.3f;
	this->farLeftSide[0] = this->position.x;
	this->farRightSide[1] = this->position.y - 0.3f;
	this->farRightSide[0] = this->position.x;

	this->animationElapsed += elapsed;
	if (this->animationElapsed > 1.0 / this->framesPerSecond) {
		this->currentIndex++;
		this->animationElapsed = 0.0;
		if (this->currentIndex > this->numFrames - 1) {
			this->currentIndex = 0;
		}
	}
	this->deathAnimationElapsed += elapsed;
	if (this->deathAnimationElapsed > 1.0 / this->deathFramesPerSecond) {
		this->deathCurrentIndex++;
		this->deathAnimationElapsed = 0.0;
		if (this->deathCurrentIndex > this->deathNumFrames - 1) {
			this->deathCurrentIndex = 0;
		}
	}

	this->position.x += this->velocity.x * elapsed;
}

void Enemy::render(ShaderProgram* program) {
	Matrix model;
	model.SetPosition(this->position.x, this->position.y, 0);
	program->SetModelMatrix(model);
	if (this->exist == true) { 
		if (this->entityType == ENTITY_SIMPLE) {
			if (this->direction == true) {
				this->DrawSpriteSheetSprite(*program, this->runAnimation[this->currentIndex], 16, 8);
			}
			else if (this->direction == false){
				model.Scale(-1.0, 1.0, 1.0);
				program->SetModelMatrix(model);
				this->DrawSpriteSheetSprite(*program, this->runAnimation[this->currentIndex], 16, 8);
			}
		}
	}
	else {
		if (death >= 0) {
			this->velocity.x = 0.0f;
			this->size.x = 1.0f;
			this->DrawSpriteSheetSprite(*program, this->deathAnimation[this->deathCurrentIndex], 16, 8);
		}
	}
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