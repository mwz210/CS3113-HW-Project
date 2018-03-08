#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include "Player.h"
#include "Enemies.h"
#include "Bullet.h"
#include "SheetSprite.h"
#include "Text.h"
#define MAX_BULLETS 10

class GameState {
	public:
		GameState();
		void initialize(GLuint planeTexture);
		Player player;
		Enemies enemy[20];
		Bullet bullets[MAX_BULLETS];
		Bullet enemyBullets[MAX_BULLETS];
		Text scoreboard;
		int bulletIndex = 0;
		int bulletIndexEnemy = 0;
		int score = 0;
		
};

#endif