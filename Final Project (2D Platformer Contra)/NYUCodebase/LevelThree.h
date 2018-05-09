#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "GameState.h"
#include "GameMode.h"
#include "SDL_mixer.h"
#include "BigBullet.h"
class LevelThree {
public:
	GameState* state;
	GameMode* mode;
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