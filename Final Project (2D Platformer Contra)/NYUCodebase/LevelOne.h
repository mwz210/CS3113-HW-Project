#ifndef LEVELONE_H
#define LEVELONE_H

#include "GameState.h"
#include "GameMode.h"
#include <math.h>
#include <SDL_mixer.h>

class LevelOne {
	public:
		GameState* state;
		GameMode* mode;

		Mix_Chunk *coin = Mix_LoadWAV("coin.wav");
		Mix_Chunk *jump = Mix_LoadWAV("jump.wav");
		Mix_Chunk *death = Mix_LoadWAV("death.wav");

		Mix_Music *gun = Mix_LoadMUS("gun.wav");

		int Mix_Open = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);


		void SetMode(GameMode* mode);
		void SetState(GameState* state);
		void ProcessEvents(float elapsed);
		void Update(float elapsed);
		void Render(ShaderProgram& program, ShaderProgram& untexture);
		void TestingPointSquareCollision();
		void TestingBulletCollision();
		const int max_bullets = 5;
		float death_count;
};



#endif // !LEVELONE_H
