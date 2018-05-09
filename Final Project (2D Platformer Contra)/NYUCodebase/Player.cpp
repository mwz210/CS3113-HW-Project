#include "Player.h"

Player::Player() {
	this->isStatic = false;
	this->entityType = ENTITY_PLAYER;
	this->size.x = .3f;
	this->size.y = .3f;
	this->acceleration.y = -0.5;
	this->exist = true;
	//this->isMoving = "none_right";
	this->isMoving = false;
	this->direction = true;		// true -> right
	this->position.x = -3.5f;
	this->position.y = -2.0f;
	this->emit.maxLifetime = 2.0f;
	this->emit.reset = false;
	this->emit.gravity.y = 0.0f;
	this->death = this->emit.maxLifetime;
	this->emit.random = true;
}

void Player::reset_collision_flags() {
	this->collidedTop = false;
	this->collidedRight = false;
	this->collidedBottom = false;
	this->collidedLeft = false;
	if (this->isMoving == true && this->direction == true) {
		this->isMoving = false;
		this->direction == true;
	}
	else if (this->isMoving == true && this->direction == false) {
		this->isMoving = false;
		this->direction = false;
	}
}

void Player::ShootBullets(Bullets& bullet, float elapsed) {
	bullet.update(elapsed, this->position, this->size, true, this->direction);
}

void Player::update(float elapsed) {
	this->emit.position.x = this->position.x;
	this->emit.position.y = this->position.y;
	if (this->exist == false) {
		this->emit.Update(elapsed);
		this->death -= elapsed;
	}
	const Uint8 *key = SDL_GetKeyboardState(NULL);
	if (this->collidedBottom == false) {
		this->acceleration.y = -1.25;
		this->velocity.y += this->acceleration.y * elapsed;
		this->position.y += this->velocity.y * elapsed;
	}
	this->position.y += this->velocity.y * elapsed;
	
	// moving on x
	if (key[SDL_SCANCODE_RIGHT] && this->position.x < 76.80f - 10.80f)
	{
		if (this->collidedRight == false) {
			this->velocity.x = 2.0f;
			this->isMoving = true;
			this->direction = true;
			this->position.x += elapsed * this->velocity.x;
		}
	}
	else if (key[SDL_SCANCODE_LEFT] && this->position.x > -4.80f)
	{
		if (this->collidedLeft == false) {
			this->velocity.x = -2.0f;
			this->isMoving = true;
			this->direction = false;
			this->position.x += elapsed * this->velocity.x;
		}
	}

	if (this->position.y <= -4.80) {
		this->exist = false;
	}
}

void Player::render(ShaderProgram* program, Matrix& model, const int runAnimation[], int currentIndex) {
	Matrix modelMatrix;
	modelMatrix.Identity();
	
	if (this->exist == true) {
		if (this->isMoving == true && this->collidedBottom == false && this->direction == false) {
			modelMatrix.SetPosition(this->position.x, this->position.y + 0.3f, 0);
			modelMatrix.Scale(-1.0f, 1.0f, 1.0f);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 83, 16, 8);
			modelMatrix.SetPosition(this->position.x, this->position.y, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 99, 16, 8);
			modelMatrix.SetPosition(this->position.x + 0.005f, this->position.y - 0.10f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 87, 16, 8);
		}
		else if (this->isMoving == true && this->collidedBottom == false && this->direction == true) {
			modelMatrix.SetPosition(this->position.x, this->position.y + 0.3f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 83, 16, 8);
			modelMatrix.SetPosition(this->position.x, this->position.y, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 99, 16, 8);
			modelMatrix.SetPosition(this->position.x - .025f, this->position.y - 0.10f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 87, 16, 8);
		}
		else if (this->isMoving == false && this->direction == true) {
			modelMatrix.SetPosition(this->position.x, this->position.y + 0.3f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 83, 16, 8);
			modelMatrix.SetPosition(this->position.x, this->position.y, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 99, 16, 8);
			modelMatrix.SetPosition(this->position.x - .025f, this->position.y - 0.10f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 87, 16, 8);
		}
		else if (this->isMoving == false && this->direction == false) {
			modelMatrix.SetPosition(this->position.x, this->position.y + 0.3f, 0);
			modelMatrix.Scale(-1.0f, 1.0f, 1.0f);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 83, 16, 8);
			modelMatrix.SetPosition(this->position.x, this->position.y, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 99, 16, 8);
			modelMatrix.SetPosition(this->position.x + 0.005f, this->position.y - 0.10f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 87, 16, 8);
		}
		else if (this->isMoving == true && this->collidedBottom == true && this->direction == true) {
			modelMatrix.SetPosition(this->position.x, this->position.y + 0.3f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 83, 16, 8);
			modelMatrix.SetPosition(this->position.x, this->position.y, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 99, 16, 8);
			modelMatrix.SetPosition(this->position.x - .025f, this->position.y - 0.10f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, runAnimation[currentIndex], 16, 8);
		}
		else if (this->isMoving == true && this->collidedBottom == true && this->direction == false) {
			modelMatrix.SetPosition(this->position.x, this->position.y + 0.3f, 0);
			modelMatrix.Scale(-1.0f, 1.0f, 1.0f);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 83, 16, 8);
			modelMatrix.SetPosition(this->position.x, this->position.y, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, 99, 16, 8);
			modelMatrix.SetPosition(this->position.x + 0.005f, this->position.y - 0.10f, 0);
			program->SetModelMatrix(modelMatrix);
			this->DrawSpriteSheetSprite(*program, runAnimation[currentIndex], 16, 8);
		}
	}
	else {
		this->emit.Render(*program, 40);
	}
}

bool Player::square_collision_detect(float* R1_sides, float* R2_sides)
{
	return(!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}

void Player::DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
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