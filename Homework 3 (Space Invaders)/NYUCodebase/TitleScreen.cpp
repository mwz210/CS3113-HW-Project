#include "TitleScreen.h"
#include "GameState.h"

void TitleScreen::Render(ShaderProgram& program) {
	Matrix viewMatrix;
	Matrix modelMatrix;
	program.SetViewMatrix(viewMatrix);
	program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	back.Draw(&program, modelMatrix);
	modelMatrix.SetPosition(this->title.position.x, this->title.position.y, this->title.position.z);
	program.SetModelMatrix(modelMatrix);
	title.DrawText(&program, title.textureId, "SPACE INVADERS", .4f, 0.0f);
	modelMatrix.SetPosition(this->start.position.x, this->start.position.y, this->start.position.z);
	program.SetModelMatrix(modelMatrix);
	title.DrawText(&program, start.textureId, "Press Enter To Start Game", .2f, -0.1f);
}

void TitleScreen::Update(ShaderProgram& program, float elapsed) {
	title.SetPosition(-2.650f, 1.00f, 0.0f);
	back.SetSpriteSheet(SheetSprite(back.textureId, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 7.0f));
	start.SetPosition(-1.250f, -1.00f, 0.0f);
}


void TitleScreen::ProcessEvents(bool& done, float elapsed) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				mode->change_mode(mode->STATE_GAME_LEVEL);
			}
		}
	}
}


bool TitleScreen::square_collision_detect(float* R1_sides, float* R2_sides)
{
	return (!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}