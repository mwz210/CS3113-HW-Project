#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "GameState.h"
#include "GameMode.h"
#include "SDL_mixer.h"
class LevelTwo {
public:
	GameState* state;
	GameMode* mode;
	Mix_Chunk *gun_not_shooting = Mix_LoadWAV("gun_not_shooting.wav");
	Mix_Chunk *explosion = Mix_LoadWAV("explosion.wav");
	Mix_Chunk *door = Mix_LoadWAV("coin.wav");
	Mix_Chunk *key = Mix_LoadWAV("key.wav");
	void SetMode(GameMode* mode);
	void SetState(GameState* state);
	void ProcessEvents(float elapsed);
	void Update(float elapsed);
	void Render(ShaderProgram& program, ShaderProgram& untexture);
	void TestingPointSquareCollision();
	void TestingBulletCollision();
	const int max_bullets = 5;
	float death_count;
	float screenShakeValue = 0;
}; 



#endif // !LEVELONE_H