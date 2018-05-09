#include "TitleScreen.h"

void TitleScreen::SetMode(GameMode* mode) {
	this->mode = mode;
}

void TitleScreen::SetState(GameState* state) {
	this->state = state;
}

void TitleScreen::Render(ShaderProgram& program) {
	Matrix viewMatrix;
	Matrix modelMatrix;
	program.SetViewMatrix(viewMatrix);
	program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	back.Draw(&program, modelMatrix);
	modelMatrix.SetPosition(this->title.position.x, this->title.position.y, this->title.position.z);
	program.SetModelMatrix(modelMatrix);
	title.DrawText(&program, title.textureId, "Shitty Contra", .9f, -0.35f);
	modelMatrix.SetPosition(this->start.position.x, this->start.position.y, this->start.position.z);
	program.SetModelMatrix(modelMatrix);
	title.DrawText(&program, start.textureId, "Press Enter To Start Game", .5f, -0.25f);
}

void TitleScreen::Update(ShaderProgram& program, float elapsed) {
	title.SetPosition(-3.10f, 1.00f, 0.0f);
	back.SetSpriteSheet(SheetSprite(back.textureId, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 11.0f));
	start.SetPosition(-2.75f, -1.00f, 0.0f);
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
				this->state->setup1("Scene_1.txt");
			}
		}
	}
}
