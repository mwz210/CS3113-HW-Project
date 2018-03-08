#include "GameLevel.h"
#include <string>

void GameLevel::ProcessEvents(bool& done, float elapsed)
{
	SDL_Event event;
	if (this->quit > 5) 
	{
		done = true;
	}
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				if (state.bullets[state.bulletIndex].position.y > 1.7f) {
					state.player.ShootBullets(state.bullets[state.bulletIndex], elapsed);
					state.bulletIndex += 1;
					if (state.bulletIndex > MAX_BULLETS - 1)
					{
						state.bulletIndex = 0;
					}
				}
			}
		}
	}
}

bool GameLevel::square_collision_detect(float* R1_sides, float* R2_sides)
{
	return (!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}

void GameLevel::Update(ShaderProgram& program, float elapsed)
{
	state.player.update(elapsed);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		state.bullets[i].update(elapsed);
		state.enemyBullets[i].update(elapsed);
	}
	bool hit_wall = false;
	if (state.enemy[19].position.x > 3.25) {
		hit_wall = true;
		state.enemy[19].position.x = 3.2499999f;
	}
	else if (state.enemy[0].position.x < -3.25) {
		hit_wall = true;
		state.enemy[0].position.x = -3.2499999f;
	}

	for (int i = 0; i < 20; i++) {
		if (hit_wall)
		{
			state.enemy[i].position.y -= .25f;
			state.enemy[i].velocity.x *= -1;
		}
		state.enemy[i].update(elapsed);
		int v1 = rand() % 10000;
		if ((v1 <= 5)) {
			if (state.enemyBullets[state.bulletIndexEnemy].position.y < -2.0f || state.enemyBullets[state.bulletIndexEnemy].position.y > 2.0f) {
				state.enemy[i].ShootBullets(state.enemyBullets[state.bulletIndexEnemy], elapsed);
				state.bulletIndexEnemy += 1;
				if (state.bulletIndexEnemy > MAX_BULLETS - 1) {
					state.bulletIndexEnemy = 0;
				}
			}
		}
		if ((square_collision_detect(state.player.sides, state.enemy[i].sides)))
		{
			state.enemy[i].exist = false;
			state.player.exist = false;
		}
		for (int k = 0; k < MAX_BULLETS; k++) {
			if (square_collision_detect(state.enemy[i].sides, state.bullets[k].sides)) {
				state.enemy[i].exist = false;
				state.bullets[k].position.y = 2000.f;
				state.enemy[i].position.y = 200.0f;
				state.score += 5;
			}
			if (square_collision_detect(state.player.sides, state.enemyBullets[k].sides)) {
				state.player.exist = false;
			}
		}
		if (state.enemy[i].position.y <= -2.00f)
		{
			state.player.exist = false;
		}
	}
	if (this->state.score >= 100) {
		this->quit += elapsed;
	}
	else if (!this->state.player.exist) {
		this->quit += elapsed;
	}
}

void GameLevel::Render(ShaderProgram& program)
{
	Matrix viewMatrix;
	Matrix modelMatrix;
	program.SetViewMatrix(viewMatrix);
	program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	if (this->state.score >= 100) {
		this->state.scoreboard.SetPosition(-2.60f, 0.0f, 0.0f);
		modelMatrix.SetPosition(this->state.scoreboard.position.x, this->state.scoreboard.position.y, this->state.scoreboard.position.z);
		program.SetModelMatrix(modelMatrix);
		this->state.scoreboard.DrawText(&program, this->state.scoreboard.textureId, "Congratulations! You Drove Away Those Pesky Aliens :).", .2f, -0.1f);
	}
	else if ((this->state.player.exist)) {

		state.player.Draw(&program, modelMatrix);
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			state.bullets[i].Draw(&program, modelMatrix);
			state.enemyBullets[i].Draw(&program, modelMatrix);
		}
		for (int i = 0; i < 20; i++) {
			state.enemy[i].Draw(&program, modelMatrix);
		}
		this->state.scoreboard.SetPosition(-3.30f, 1.60f, 0.0f);
		modelMatrix.SetPosition(this->state.scoreboard.position.x, this->state.scoreboard.position.y, this->state.scoreboard.position.z);
		program.SetModelMatrix(modelMatrix);
		this->state.scoreboard.DrawText(&program, this->state.scoreboard.textureId, "Score:" + std::to_string(this->state.score), .2f, 0.0f);
	}

	else  {
		this->state.scoreboard.SetPosition(-1.60f, 0.0f, 0.0f);
		modelMatrix.SetPosition(this->state.scoreboard.position.x, this->state.scoreboard.position.y, this->state.scoreboard.position.z);
		program.SetModelMatrix(modelMatrix);
		this->state.scoreboard.DrawText(&program, this->state.scoreboard.textureId, "Game Over", .4f, 0.0f);
	}
		

}