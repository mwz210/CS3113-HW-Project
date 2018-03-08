#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#pragma once

#include "GameState.h"

class GameLevel {
	public:
		GameState state;
		void ProcessEvents(bool& done, float elapsed);
		bool square_collision_detect(float* R1_sides, float* R2_sides);
		void Update(ShaderProgram& program, float elapsed);
		void Render(ShaderProgram& program);
		float pause = 0;
		float quit = 0;
};

#endif GAMELEVEL_H