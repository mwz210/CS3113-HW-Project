#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include "Player.h"
#include "Bullets.h"
#include "SheetSprite.h"
#include "Text.h"
#include "Coin.h"
#include "Bounce.h"
#include "Enemy.h"
#include "FlareMap.h"
#include "Ground.h"
#include "ParticleEmitter.h"
#include <string>
#include "key.h"
#include "door.h"
#include "Boss.h"
#include "SDL_mixer.h"
#include "BigBullet.h"
#define MAX_BULLETS 5
#define MAX_BIGBULLETS 2

class GameState {
public:
	GameState();
	void PlaceEntity(std::string type, float x, float y);
	void setup1(std::string map);
	void reset1();

	FlareMap map;
	GLuint sprite;

	// Matrices
	Matrix modelMatrix;
	Matrix viewMatrix;
	Matrix backModel;
	Matrix backView;

	//boolean for process event
	bool done = false;

	//float for elapsed time
	float lastFrameTicks = 0.0f;

	//Game objects and related animations
	Player player;
	Boss boss;
	Key key;
	std::vector<Ground> grass;
	std::vector<Coin> coins;
	std::vector<Bounce> bounces;
	Bullets bullets[MAX_BULLETS];
	BigBullet bigBullets[MAX_BIGBULLETS];
	std::vector<ParticleEmitter> particles;
	std::vector<Enemy> enemies;
	std::vector<Door> doors;
	int bigIndex = 0;
	int bulletIndex = 0;
	float accumulator = 0.0f;

	const int runAnimation[8] = { 64,65,66,67,68,69,70,71 };
	const int numFrames = 8;
	float animationElapsed = 0.0f;
	float framesPerSecond = 10.0f;
	int currentIndex = 0;

	const int runAnimationCoin[4] = { 51, 52, 53, 54 };
	const int numCoinFrames = 4;
	float animationElapsedCoin = 0.0f;
	float framesPerSecondCoin = 10.0f;
	int currentIndexCoin = 0;
};

#endif