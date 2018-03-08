#include "Bullet.h"

Bullet::Bullet() {
	this->velocity.y = 2.0f;
	exist = true;
}

void Bullet::Identity()
{
	position.Identity();

	velocity.Identity();

	size.Identity();
}

void Bullet::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Bullet::SetVelocity(float x, float y, float z)
{

	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Bullet::SetSize(float x, float y, float z)
{
	size.x = x;
	size.y = y;
	size.z = z;
}

void Bullet::SetRotation(float rotate)
{
	rotation = rotate;
}

void Bullet::Draw(ShaderProgram *program, Matrix& model)
{
	if (exist) {
		model.SetPosition(this->position.x, this->position.y, this->position.z);
		program->SetModelMatrix(model);
		sheet.Draw(program);
	}
}

void Bullet::update(float elapsed, Vector3& position, Vector3& other_size, bool shoot)
{
	if (shoot)
	{
		this->SetPosition(position.x, position.y + (other_size.y / 2) + (size.y / 2), position.z);
	}
}

void Bullet::update(float elapsed, Vector3& position, Vector3& other_size) {
	this->SetPosition(position.x, position.y - (other_size.y / 2) - (size.y / 2), position.z);
}

void Bullet::update(float elapsed)
{
	this->position.y += elapsed * this->velocity.y;
	sides[0] = this->position.y + .01f;
	sides[1] = this->position.y - .01f;
	sides[2] = this->position.x + .005f;
	sides[3] = this->position.x - .005f;
}

void Bullet::SetSpriteSheet(SheetSprite& sprite)
{
	sheet = sprite;
	size.x = sheet.size * 1 * (sheet.width / sheet.height);
	size.y = sheet.size * 1;
}

void Bullet::ChangeModel(Matrix& model)
{
	model.SetPosition(this->position.x, this->position.y, this->position.z);
}
