#include "Player.h"

Player::Player() {
	this->isStatic = false;
	this->entityType = ENTITY_PLAYER;
	this->size.x = .4f;
	this->size.y = .4f;
	this->acceleration.y = -0.5;
	this->exist = true;
}

void Player::reset_collision_flags() {
	this->collidedTop = false;
	this->collidedRight = false;
	this->collidedBottom = false;
	this->collidedLeft = false;
	this->isMoving = false;
}

void Player::ShootBullets(Bullets& bullet, float elapsed) {
	bullet.update(elapsed, this->position, this->size, true);
}

void Player::update(float elapsed) {
	const Uint8 *key = SDL_GetKeyboardState(NULL);

	if (this->collidedBottom == false) {
		this->acceleration.y = -1.0;
		this->velocity.y += this->acceleration.y * elapsed;
		this->position.y += this->velocity.y * elapsed;
	}
	this->position.y += this->velocity.y * elapsed;
	
	// moving on x
	if (key[SDL_SCANCODE_RIGHT] && this->position.x < 51.20f - 6.45f)
	{
		this->position.x += elapsed * 2.0f;
		this->isMoving = true;
	}
	else if (key[SDL_SCANCODE_LEFT] && this->position.x > -5.65f)
	{
		this->position.x -= elapsed * 2.0f;
		this->isMoving = true;
	}
}

void Player::render(ShaderProgram* program, Matrix& model, const int runAnimation[], int currentIndex) {
	model.SetPosition(this->position.x, this->position.y, 0);
	program->SetModelMatrix(model);
	
	if (this->exist == true) {
		if (this->isMoving == false) {
			this->DrawSpriteSheetSprite(*program, 81, 16, 8);
		}
		else {
			this->DrawSpriteSheetSprite(*program, runAnimation[currentIndex], 16, 8);
		}
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