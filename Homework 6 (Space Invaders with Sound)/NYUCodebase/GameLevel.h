#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#pragma once

#include "GameState.h"
#include <SDL_mixer.h>


class GameLevel {
	public:
		int Mix_Open = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		Mix_Chunk *gun = Mix_LoadWAV("gun.wav");
		Mix_Chunk *explosion = Mix_LoadWAV("explosion.wav");
		GameState state;
		void ProcessEvents(bool& done, float elapsed);
		bool square_collision_detect(float* R1_sides, float* R2_sides);
		void Update(ShaderProgram& program, float elapsed);
		void Render(ShaderProgram& program);
		float pause = 0;
		float quit = 0;
};

#endif GAMELEVEL_H