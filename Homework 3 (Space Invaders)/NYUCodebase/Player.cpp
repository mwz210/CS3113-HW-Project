#include "Player.h"
#include "Bullet.h"

Player::Player() {
	exist = true;
}

void Player::ShootBullets(Bullet& bullet, float elapsed)
{
	bullet.update(elapsed, this->position, this->size, true);
}


void Player::Identity()
{
	position.Identity();

	velocity.Identity();

	size.Identity();
}

void Player::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Player::SetVelocity(float x, float y, float z)
{

	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Player::SetSize(float x, float y, float z)
{
	size.x = x;
	size.y = y;
	size.z = z;
}

void Player::SetRotation(float rotate)
{
	rotation = rotate;
}

void Player::SetSpriteSheet(SheetSprite sheet)
{
	sprite = sheet;
	size.x = sheet.size * 1 * (sheet.width/sheet.height);
	size.y = sheet.size * 1;
}

void Player::Draw(ShaderProgram *program, Matrix& model)
{
	if (this->exist) {
		model.SetPosition(this->position.x, this->position.y, this->position.z);
		program->SetModelMatrix(model);
		sprite.Draw(program);
	}
}

void Player::update(float elapsed)
{
	const Uint8 *key = SDL_GetKeyboardState(NULL);
	if (key[SDL_SCANCODE_RIGHT] && this->position.x < 3.20f)
	{
		this->position.x += elapsed * 2.0f;
	}
	else if (key[SDL_SCANCODE_LEFT] && this->position.x > -3.20f)
	{
		this->position.x -= elapsed * 2.0f;
	}
	sides[0] = this->position.y + .15f;
	sides[1] = this->position.y - .15f;
	sides[2] = this->position.x + .15f;
	sides[3] = this->position.x - .15f;
}

void Player::ChangeModel(Matrix& model)
{
	model.SetPosition(this->position.x, this->position.y, this->position.z);
}

