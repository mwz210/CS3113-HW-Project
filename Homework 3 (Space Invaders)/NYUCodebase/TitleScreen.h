#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#pragma once
#include "ShaderProgram.h"
#include "Text.h"
#include "Background.h"
#include "GameMode.h"

class TitleScreen {
	public:
		Text title;
		Background back;
		Text start;
		GameMode* mode;


		void SetMode(GameMode& mode);
		void ProcessEvents(bool& done, float elapsed);
		bool square_collision_detect(float* R1_sides, float* R2_sides);
		void Update(ShaderProgram& program, float elapsed);
		void Render(ShaderProgram& program);
};

#endif