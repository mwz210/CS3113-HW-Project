#include "GameState.h"

GameState::GameState() {}

void GameState::initialize(GLuint planeTexture) {
	SheetSprite plane(planeTexture, 777.0f / 1024.0f, 443.0f / 1024.0f, 32.0f / 1024.0f, 26.0f / 1024.0f, 0.2f);
	player.SetSpriteSheet(plane);
	player.SetPosition(0.0f, -1.50f, 0.0f);
	float position = -2.50f;
	for (int i = 0; i < 20; i++)
	{
		enemy[i].SetSpriteSheet(SheetSprite(planeTexture, 425.0f / 1024.0f, 468.0f / 1024.0f, 93.0f / 1024.0f, 84.0f / 1024.0f, 0.2f));
		if (i == 0)
		{
			enemy[0].position.y = 1.25f;
			enemy[0].position.x = (position + ((5.0 / 5.0)*(i % 5)));
		}
		else if (i < 5)
		{
			enemy[i].position.y = 1.25f;
			enemy[i].position.x = (position + ((5.0 / 5.0)*(i % 5)));
		}
		else if (i < 10) {
			enemy[i].position.y = 1.00f;
			enemy[i].position.x = (position + ((5.0 / 5.0)*(i % 5)));
		}
		else if (i < 15) {
			enemy[i].position.y = .75f;
			enemy[i].position.x = (position + ((5.0 / 5.0)*(i % 5)));
		}
		else {
			enemy[i].position.y = .50f;
			enemy[i].position.x = (position + ((5.0 / 5.0)*(i % 5)));
		}

	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i].position.y = 2000.f;
		bullets[i].SetSpriteSheet(SheetSprite(planeTexture, 858.0f / 1024.0f, 230.0f / 1024.0f, 9.0f / 1024.0f, 54.0f / 1024.0f, 0.2f));
		enemyBullets[i].position.y = -2000.f;
		enemyBullets[i].SetSpriteSheet(SheetSprite(planeTexture, 827.0f / 1024.0f, 125.0f / 1024.0f, 16.0f / 1024.0f, 40.0f / 1024.0f, 0.1f));
		enemyBullets[i].velocity.y *= -1;
	}
}