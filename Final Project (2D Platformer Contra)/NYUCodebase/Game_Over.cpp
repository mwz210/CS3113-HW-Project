#include "Game_Over.h"

void Game_Over::SetMode(GameMode* mode) {
	this->mode = mode;
}

void Game_Over::Render(ShaderProgram& program) {
	Matrix viewMatrix;
	Matrix modelMatrix;
	program.SetViewMatrix(viewMatrix);
	program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	if (this->mode->mode == this->mode->STATE_WIN_GAME) {
		back.Draw(&program, modelMatrix);
		modelMatrix.SetPosition(this->title.position.x, this->title.position.y, this->title.position.z);
		program.SetModelMatrix(modelMatrix);
		title.DrawText(&program, title.textureId, "Congrats for beating this shitty game", .5f, -0.30f);
		modelMatrix.SetPosition(this->start.position.x, this->start.position.y, this->start.position.z);
		program.SetModelMatrix(modelMatrix);
		title.DrawText(&program, start.textureId, "Start Over and Find Out More? Press Enter.", .5f, -0.29f);
		modelMatrix.SetPosition(this->start.position.x, this->start.position.y - 1.0f, this->start.position.z);
		program.SetModelMatrix(modelMatrix);
		title.DrawText(&program, start.textureId, "There is lots of bugs... Press Q to Quit", .45f, -0.25f);
	}
	else {
		back.Draw(&program, modelMatrix);
		modelMatrix.SetPosition(this->title.position.x, this->title.position.y, this->title.position.z);
		program.SetModelMatrix(modelMatrix);
		title.DrawText(&program, title.textureId, "Feels bad and no save :(.", .6f, -0.30f);
		modelMatrix.SetPosition(this->start.position.x, this->start.position.y, this->start.position.z);
		program.SetModelMatrix(modelMatrix);
		title.DrawText(&program, start.textureId, "Start Over and Lose Again? Press Enter.", .5f, -0.29f);
		modelMatrix.SetPosition(this->start.position.x, this->start.position.y - 1.0f, this->start.position.z);
		program.SetModelMatrix(modelMatrix);
		title.DrawText(&program, start.textureId, "Else Press Q to Quit, Loser.", .5f, -0.25f);
	}
	
}

void Game_Over::Update(ShaderProgram& program, float elapsed) {
	title.SetPosition(-3.35f, 1.00f, 0.0f);
	back.SetSpriteSheet(SheetSprite(back.textureId, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 1024.0f / 1024.0f, 11.0f));
	start.SetPosition(-3.75f, -1.00f, 0.0f);
}


void Game_Over::ProcessEvents(bool& done, float elapsed) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				mode->change_mode(mode->STATE_TITLE_SCREEN);
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
				done = true;
			}
		}
	}
}
