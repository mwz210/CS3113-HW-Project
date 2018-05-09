#include "GameState.h"

GameState::GameState() {
}

void GameState::PlaceEntity(std::string type, float x, float y) {
	if (type == "Coin") {
		Coin coin;
		coin.position.x = x;
		coin.position.y = y;
		this->coins.push_back(coin);
	}
	// Create Coin Object
	else if (type == "Bounce") {
		Bounce bounce;
		bounce.position.x = x;
		bounce.position.y = y;
		this->bounces.push_back(bounce);
	}
	else if (type == "enemy_simple") {
		Enemy enemy;
		enemy.entityType = enemy.ENTITY_SIMPLE;
		enemy.position.x = x;
		enemy.position.y = y;
		this->enemies.push_back(enemy);
	}
	else if (type == "key") {
		Key key;
		this->key = key;
		this->key.position.x = x;
		this->key.position.y = y;
	}
	else if (type == "door") {
		Door door;
		door.position.x = x;
		door.position.y = y;
		this->doors.push_back(door);
	}
}

void GameState::setup1(std::string map) {
	for (int i = 0; i < 5; i++) {
		this->bullets[i].position.x = 30000.f;
	}

	for (int i = 0; i < 2; i++) {
		this->bigBullets[i].position.x = 30000.f;
	}

	// FlareMap
	this->map.Load(map);

	float y_position = 4.86;
	float x_position = -4.83;

	// Traversing 2d array data
	for (int y = 0; y < this->map.mapHeight; y++) {
		for (int x = 0; x < this->map.mapWidth; x++) {
			if (this->map.mapData[y][x] != 0)
			{
				Ground solid;
				solid.position.x = x_position;
				solid.position.y = y_position;
				solid.mapData = this->map.mapData[y][x];
				this->grass.push_back(solid);
			}
			x_position += .3;
		}
		x_position = -4.83;
		y_position -= .3f;
	}

	for (int i = 0; i < this->map.entities.size(); i++) {
		this->map.entities[i].x *= 0.3f;
		this->map.entities[i].x -= 4.83;
		this->map.entities[i].y -= 1.00f;
		this->map.entities[i].y *= -0.3f;
		this->map.entities[i].y += 4.86f;
		PlaceEntity(this->map.entities[i].type, this->map.entities[i].x, this->map.entities[i].y);
	}

	if (map == "Scene_3") {
		this->boss.position.x = 4.0f;
		this->boss.position.y = 0.0f;
	}
}

void GameState::reset1() {
	this->modelMatrix.Identity();
	this->backView.Identity();
	this->viewMatrix.Identity();
	this->backModel.Identity();
	this->lastFrameTicks = 0.0f;
	this->grass.clear();
	this->enemies.clear();
	this->coins.clear();
	this->bounces.clear();
	this->particles.clear();
	this->bulletIndex = 0;
	this->accumulator = 0.0f;
	this->animationElapsed = 0.0f;
	this->animationElapsedCoin = 0.0f;
	this->currentIndex = 0.0f;
	this->currentIndexCoin = 0.0f;
	this->player.position.x = -3.5f;
	this->player.position.y = -2.0f;
	this->player.exist = true;
	this->player.direction = true;
	FlareMap map;
	this->map = map;
	this->player.coins = 0;
	this->player.key = false;
	this->doors.clear();
	Key key;
	this->key = key;
	this->player.death = 2.0f;
	this->boss.position.x = 3.5f;
	this->boss.position.y = -3.00f;
	this->boss.exist = true;
	this->boss.position.y = -3.00f;
	this->boss.death = 1.0f;
	this->boss.bored = false;
	this->boss.shoot = false;
	this->boss.hide = true;
}