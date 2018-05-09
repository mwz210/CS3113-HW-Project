#include "Boss.h"

Boss::Boss() {
	this->isStatic = false;
	this->size.x = 1.5f;
	this->size.y = 1.5f;
	this->exist = true;
	this->position.x = 3.5f;
	this->position.y = -3.00f;
	this->death = 1.0f;
	this->bored = false;
	this->shoot = false;
	this->hide = true;
	this->part.position.x = this->position.x;
	this->part.position.y = this->position.y;
	this->part.startSize = 1.5f;
	this->part.endSize = 0.5f;
	this->part.sizeDeviation = 0.5f;
	this->part.maxLifetime = 2.0f;
	this->part.reset = false;
	this->part.gravity.y = 0.0f;
	this->death = this->part.maxLifetime;
	this->part.random = true;
	this->health = 100;
}

void Boss::ShootMud(BigBullet& bullet, float elapsed) {
	bullet.update(elapsed, this->position, this->size, true, false);
}

void Boss::update(float elapsed) {
	if (this->exist == false) {
		this->death -= elapsed;
	}
	const Uint8 *key = SDL_GetKeyboardState(NULL);
	this->rightSide[1] = this->position.y;
	this->rightSide[0] = this->position.x + .15f;
	this->leftSide[1] = this->position.y;
	this->leftSide[0] = this->position.x - .15f;
	this->AnimationElapsed += elapsed;
	if (this->AnimationElapsed > 1.0 / this->FramesPerSecond) {
		this->CurrentIndex++;
		this->AnimationElapsed = 0.0;
		if (this->CurrentIndex > this->NumFrames - 1) {
			this->CurrentIndex = 0;
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

void Boss::render(ShaderProgram* program) {
	Matrix model;
	model.SetPosition(this->position.x, this->position.y, 0);
	program->SetModelMatrix(model);
	if (this->exist == true) {
		if (this->shoot == true) {
			this->DrawSpriteSheetSprite(*program, this->runAnimation[this->CurrentIndex], 16, 8);
			model.SetPosition(this->position.x, this->position.y + 1.5f, 0);
			program->SetModelMatrix(model);
			this->DrawSpriteSheetSprite(*program, this->deathAnimation[this->deathCurrentIndex], 16, 8);
		}
		else if (this->hurt == true) {
			this->DrawSpriteSheetSprite(*program, 30, 16, 8);
			model.SetPosition(this->position.x, this->position.y + 1.5f, 0);
			program->SetModelMatrix(model);
			this->DrawSpriteSheetSprite(*program, 14, 16, 8);
			this->hurt = false;
		}
		else if (this->hide == true) {
			this->DrawSpriteSheetSprite(*program, 28, 16, 8);
			model.SetPosition(this->position.x, this->position.y + 1.5f, 0);
			program->SetModelMatrix(model);
			this->DrawSpriteSheetSprite(*program, 12, 16, 8);
		}
		else if (this->bored == true) {
			this->DrawSpriteSheetSprite(*program, 29, 16, 8);
			model.SetPosition(this->position.x, this->position.y + 1.5f, 0);
			program->SetModelMatrix(model);
			this->DrawSpriteSheetSprite(*program, 13, 16, 8);
		}
	}
	else {
		if (death >= 0) {
			this->part.Render(*program, 40);
		}
		else {
			this->position.y = -300.0f;
		}
	}
}

bool Boss::square_collision_detect(float* R1_sides, float* R2_sides)
{
	return(!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}

void Boss::DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
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