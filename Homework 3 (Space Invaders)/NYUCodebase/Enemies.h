#pragma once
#ifndef ENEMIES_H
#define ENEMIES_H
#include "Player.h"

class Enemies: public Player{
	public:
		Enemies();
		void update(float elapsed);
		void ShootBullets(Bullet& bullet, float elapsed);
};

#endif 