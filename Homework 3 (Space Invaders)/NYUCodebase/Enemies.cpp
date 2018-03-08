#include "Enemies.h"

Enemies::Enemies() {
	this->SetVelocity(.8f, 0.0f, 0.0f);
	this->exist = true;
}

void Enemies::update(float elapsed) {
	this->position.x += this->velocity.x * elapsed;	
	sides[0] = this->position.y + .15f;
	sides[1] = this->position.y - .15f;
	sides[2] = this->position.x + .15f;
	sides[3] = this->position.x - .15f;
}

void Enemies::ShootBullets(Bullet& bullet, float elapsed)
{
	bullet.update(elapsed, this->position, this->size);
}
