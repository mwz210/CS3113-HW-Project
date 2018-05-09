#include "Bullets.h"

Bullets::Bullets() {
	this->velocity.x = 8.0f;
	this->size.x = .4f;
	this->size.y = .4f;
	this->hit = false;
}

void Bullets::Identity()
{
	position.Identity();

	velocity.Identity();

	size.Identity();
}

void Bullets::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Bullets::SetVelocity(float x, float y, float z)
{

	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

void Bullets::SetSize(float x, float y, float z)
{
	size.x = x;
	size.y = y;
	size.z = z;
}

void Bullets::SetRotation(float rotate)
{
	rotation = rotate;
}

void Bullets::Draw(ShaderProgram *program, Matrix& model)
{
	model.SetPosition(this->position.x, this->position.y, this->position.z);
	program->SetModelMatrix(model);
	this->DrawSpriteSheetSprite(*program, 21, 16, 8);
}

void Bullets::update(float elapsed, Vector3& position, Vector3& other_size, bool shoot, bool direction)
{
	if (shoot && (direction == true))
	{
		this->velocity.x = 8.0f;
		this->SetPosition(position.x + ((other_size.x / 2) - .25f) + (this->size.x / 2), position.y - .075f, position.z);
		this->limit = this->position.x + 8.0f;
		this->directionShot = true;
	}
	else if (shoot && (direction == false)) {

		this->velocity.x = -8.0f;
		this->SetPosition(position.x - ((other_size.x / 2) + .10f) + (this->size.x / 2), position.y - .075f, position.z);
		this->limit = this->position.x - 8.0f;
		this->directionShot = false;
	}
}

void Bullets::update(float elapsed, Vector3& position, Vector3& other_size) {
	this->SetPosition(position.x, position.y - (other_size.y / 2) - (size.y / 2), position.z);
}

void Bullets::update(float elapsed)
{
	this->position.x += elapsed * this->velocity.x;
	sides[0] = this->position.y + .2f;
	sides[1] = this->position.y - .2f;
	sides[2] = this->position.x + .2f;
	sides[3] = this->position.x - .2f;
	if (this->limit <= this->position.x && this->directionShot == true) {
		this->position.x = 30000.0f;
	}
	else if (this->limit >= this->position.x && this->directionShot == false){
		this->position.x = 30000.0f;
		this->velocity.x = 8.0f;
	}
}

void Bullets::ChangeModel(Matrix& model)
{
	model.SetPosition(this->position.x, this->position.y, this->position.z);
}

void Bullets::DrawSpriteSheetSprite(ShaderProgram& program, int index, int spriteCountX, int spriteCountY) {
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