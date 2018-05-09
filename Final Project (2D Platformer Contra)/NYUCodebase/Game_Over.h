#ifndef GAME_OVER_H
#define GAME_OVER_H
#include "ShaderProgram.h"
#include "Text.h"
#include "Background.h"
#include "GameMode.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class Game_Over {
public:
	Text title;
	Background back;
	Text start;
	GameMode* mode;
	int score;
	//Mix_Chunk *gun = Mix_LoadWAV("gun.wav");
	//Mix_Chunk *explosion = Mix_LoadWAV("explosion.wav");

	void SetMode(GameMode* mode);
	void ProcessEvents(bool& done, float elapsed);
	bool square_collision_detect(float* R1_sides, float* R2_sides);
	void Update(ShaderProgram& program, float elapsed);
	void Render(ShaderProgram& program);
};

#endif
