#include "LevelThree.h"
#include <math.h>

void LevelThree::TestingPointSquareCollision() {
	// Declaring points on player rectangle
	float bottomSide[2];
	float topSide[2];
	float rightSide[2];
	float leftSide[2];
	float leftTopSide[2];
	float leftBottomSide[2];
	float rightTopSide[2];
	float rightBottomSide[2];
	// Initializing points on player rectangle
	bottomSide[1] = this->state->player.position.y - .255f;
	bottomSide[0] = this->state->player.position.x;
	topSide[1] = this->state->player.position.y + .16f;
	topSide[0] = this->state->player.position.x;
	rightSide[1] = this->state->player.position.y;
	rightSide[0] = this->state->player.position.x + .15f;
	leftSide[1] = this->state->player.position.y;
	leftSide[0] = this->state->player.position.x - .15f;

	leftTopSide[0] = this->state->player.position.x - .15f;
	leftTopSide[1] = this->state->player.position.y + .11f;
	leftBottomSide[0] = this->state->player.position.x - .15f;
	leftBottomSide[1] = this->state->player.position.y - .20f;
	rightTopSide[0] = this->state->player.position.x + .15f;
	rightTopSide[1] = this->state->player.position.y + .11f;
	rightBottomSide[0] = this->state->player.position.x + .15f;
	rightBottomSide[1] = this->state->player.position.y - .20f;

		// Checking all collision stuff 
	for (int i = 0; i < this->state->grass.size(); i++) {

		// Setting grass boxes
		float boxTop = this->state->grass[i].position.y + .15f;
		float boxBottom = this->state->grass[i].position.y - .15f;
		float boxRight = this->state->grass[i].position.x + .15f;
		float boxLeft = this->state->grass[i].position.x - .15f;

		// Logic for point and box collision. All points on player.
		if ((bottomSide[0] > boxLeft && bottomSide[0] < boxRight) && (bottomSide[1] > boxBottom && bottomSide[1] < boxTop)) {
			this->state->player.collidedBottom = true;
			float penetration = fabs((this->state->player.position.y - this->state->grass[i].position.y) - .255 - .15);
			this->state->player.position.y += penetration - 0.001;
		}
		if ((topSide[0] > boxLeft && topSide[0] < boxRight) && (topSide[1] > boxBottom && topSide[1] < boxTop)) {
			this->state->player.collidedTop = true;
			float penetration = fabs((this->state->grass[i].position.y - this->state->player.position.y) - .16 - .15);
			this->state->player.position.y -= penetration - 0.001;
		}
		if (((leftSide[0] > boxLeft && leftSide[0] < boxRight) && (leftSide[1] > boxBottom && leftSide[1] < boxTop)) ||
			((leftBottomSide[0] > boxLeft && leftBottomSide[0] < boxRight) && (leftBottomSide[1] > boxBottom && leftBottomSide[1] < boxTop)) ||
			((leftTopSide[0] > boxLeft && leftTopSide[0] < boxRight) && (leftTopSide[1] > boxBottom && leftTopSide[1] < boxTop))) {
			this->state->player.collidedLeft = true;
			float penetration = fabs((this->state->player.position.x - this->state->grass[i].position.x) - .15 - .15);
			this->state->player.position.x += penetration - 0.001;
		}
		if (((rightSide[0] > boxLeft && rightSide[0] < boxRight) && (rightSide[1] > boxBottom && rightSide[1] < boxTop)) ||
			((rightTopSide[0] > boxLeft && rightTopSide[0] < boxRight) && (rightTopSide[1] > boxBottom && rightTopSide[1] < boxTop)) ||
			((rightBottomSide[0] > boxLeft && rightBottomSide[0] < boxRight) && (rightBottomSide[1] > boxBottom && rightBottomSide[1] < boxTop))) {
			this->state->player.collidedRight = true;
			float penetration = fabs((this->state->grass[i].position.x - this->state->player.position.x) - .15 - .15);
			this->state->player.position.x -= penetration - 0.001;
		}
	}

	// Checking all collision stuff 
	for (int i = 0; i < 2; i++) {

		// Setting grass boxes
		float boxTop = this->state->bigBullets[i].position.y + .30f;
		float boxBottom = this->state->bigBullets[i].position.y - .30f;
		float boxRight = this->state->bigBullets[i].position.x + .30f;
		float boxLeft = this->state->bigBullets[i].position.x - .30f;

		// Logic for point and box collision. All points on player.
		if ((bottomSide[0] > boxLeft && bottomSide[0] < boxRight) && (bottomSide[1] > boxBottom && bottomSide[1] < boxTop)) {
			this->state->player.exist = false;
		}
		if ((topSide[0] > boxLeft && topSide[0] < boxRight) && (topSide[1] > boxBottom && topSide[1] < boxTop)) {
			this->state->player.exist = false;
		}
		if (((leftSide[0] > boxLeft && leftSide[0] < boxRight) && (leftSide[1] > boxBottom && leftSide[1] < boxTop)) ||
			((leftBottomSide[0] > boxLeft && leftBottomSide[0] < boxRight) && (leftBottomSide[1] > boxBottom && leftBottomSide[1] < boxTop)) ||
			((leftTopSide[0] > boxLeft && leftTopSide[0] < boxRight) && (leftTopSide[1] > boxBottom && leftTopSide[1] < boxTop))) {
			this->state->player.exist = false;
		}
		if (((rightSide[0] > boxLeft && rightSide[0] < boxRight) && (rightSide[1] > boxBottom && rightSide[1] < boxTop)) ||
			((rightTopSide[0] > boxLeft && rightTopSide[0] < boxRight) && (rightTopSide[1] > boxBottom && rightTopSide[1] < boxTop)) ||
			((rightBottomSide[0] > boxLeft && rightBottomSide[0] < boxRight) && (rightBottomSide[1] > boxBottom && rightBottomSide[1] < boxTop))) {
			this->state->player.exist = false;
		}
	}
	// Traverse through solid blocks 
}

void LevelThree::TestingBulletCollision() {
	float enemy_sides[4] =
	{
		this->state->boss.position.y + 1.5,
		this->state->boss.position.y - .50,
		this->state->boss.position.x + .75,
		this->state->boss.position.x - .75
	};
	for (int i = 0; i < this->max_bullets; i++) {
		float bullet_sides[4] =
		{ this->state->bullets[i].position.y + .15,
			this->state->bullets[i].position.y - .15,
			this->state->bullets[i].position.x + .15,
			this->state->bullets[i].position.x - .15 };
		if (this->state->boss.square_collision_detect(enemy_sides, bullet_sides)) {
			this->state->bullets[i].position.x = 30000.f;
			if (this->state->boss.bored == true) {
				this->state->boss.health -= 2;
				this->state->boss.hurt = true;
			}
			else if (this->state->boss.hide == true) {
				this->state->boss.health -= 0;
			}
			else {
				this->state->boss.health -= 5;
				this->state->boss.hurt = true;
			}
		}
	}
}

void LevelThree::SetMode(GameMode* mode) {
	this->mode = mode;
}

void LevelThree::SetState(GameState* game_state) {
	this->state = game_state;
}

void LevelThree::ProcessEvents(float elapsed) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			this->state->done = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			// Jump for Player
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				if (this->state->player.collidedBottom == true) {
					this->state->player.velocity.y = 1.00f;
				}
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_Z) {
				if (this->state->bullets[this->state->bulletIndex].position.x > 100.0f) {
					this->state->player.ShootBullets(this->state->bullets[this->state->bulletIndex], elapsed);
					this->state->bulletIndex += 1;
					if (this->state->bulletIndex > MAX_BULLETS - 1) {
						this->state->bulletIndex = 0;
					}
				}
			}
		}
	}
}

void LevelThree::Update(float elapsed) {
	/*
	float bossSide[4];
	bossSide[0] = boss.position.y + 1.0f;
	bossSide[1] = boss.position.y - 1.0f;
	bossSide[2] = boss.position.x + .5f;
	bossSide[3] = boss.position.x - .5f;
	*/
	if (this->state->boss.health <= 0) {
		this->state->boss.exist = false;
		this->state->viewMatrix.Translate(0.0f, sin(this->screenShakeValue * 20.0f) * 0.2f, 0.0f);
	}
	this->state->boss.update(elapsed);
	this->state->animationElapsed += elapsed;
	this->state->animationElapsedCoin += elapsed;
	this->screenShakeValue += elapsed;
	float difference = this->state->boss.position.x - this->state->player.position.x;
	if (difference > 6.5 && this->state->boss.health > 35) {
		this->state->boss.bored = false;
		this->state->boss.hide = true;
		this->state->boss.shoot = false;
	}
	else if (difference < 3.00) {
		this->state->boss.bored = false;
		this->state->boss.hide = false;
		this->state->boss.shoot = true;
	}
	else {
		this->state->boss.bored = true;
		this->state->boss.hide = false;
		this->state->boss.shoot = false;
	}
	if (this->state->boss.health < 35) {
		this->state->boss.shoot = true;
		this->state->boss.bored = false;
		this->state->boss.hide = false;
	}
	//boss.reset_collision_flags();
	this->state->player.reset_collision_flags();
	for (int i = 0; i < this->state->enemies.size(); i++) {
		this->state->enemies[i].reset_collision_flags();
		if (this->state->enemies[i].death <= 0) {
			this->state->enemies[i].position.y = -300.0f;
		}
	}

	TestingPointSquareCollision();
	TestingBulletCollision();

	if (this->state->boss.position.y < -100) {
		this->mode->change_mode(mode->STATE_WIN_GAME);
		this->state->reset1();
	}

	if (this->state->boss.shoot == true) {
		if (this->state->bigBullets[this->state->bigIndex].position.x > 100.0f) {
			this->state->boss.ShootMud(this->state->bigBullets[this->state->bigIndex], elapsed);
			this->state->viewMatrix.Translate(sin(this->screenShakeValue * 20.0f) * 0.2f, 0.0f, 0.0f);
			this->state->bulletIndex += 1;
			if (this->state->bulletIndex > MAX_BULLETS - 1) {
				this->state->bulletIndex = 0;
			}
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		this->state->bullets[i].update(elapsed);
	}

	for (int i = 0; i < MAX_BIGBULLETS; i++) {
		this->state->bigBullets[i].update(elapsed);
	}

	state->player.update(elapsed);

	if (this->state->animationElapsed > 1.0 / this->state->framesPerSecond) {
		this->state->currentIndex++;
		this->state->animationElapsed = 0.0;
		if (this->state->currentIndex > this->state->numFrames - 1) {
			this->state->currentIndex = 0;
		}
	}
	if (this->state->animationElapsedCoin > 1.0 / this->state->framesPerSecondCoin) {
		this->state->currentIndexCoin++;
		this->state->animationElapsedCoin = 0.0;
		if (this->state->currentIndexCoin > this->state->numCoinFrames - 1) {
			this->state->currentIndexCoin = 0;
		}
	}
}

void LevelThree::Render(ShaderProgram& program, ShaderProgram& untexture) {
	if (this->state->player.exist == false && this->state->player.death <= 0) {
		this->state->reset1();
		this->mode->change_mode(mode->STATE_GAME_OVER);
	}
	// Background
	glBindTexture(GL_TEXTURE_2D, this->state->sprite);
	//this->state->player.position.x = 20.30f;
	if (this->state->player.position.x > 0 && this->state->player.position.x < 28.00f) {
		if (this->state->player.position.y > 0.00 && this->state->player.position.y < 5.80) {
			this->state->viewMatrix.SetPosition(-this->state->player.position.x, -this->state->player.position.y, 0);
		}
		else {
			this->state->viewMatrix.SetPosition(-this->state->player.position.x, 0, 0);
		}
	}
	program.SetViewMatrix(this->state->viewMatrix);
	untexture.SetColor(0.0f, 0.749f, 1.0f, 1.0f);
	untexture.SetModelMatrix(this->state->backModel);
	untexture.SetViewMatrix(this->state->backView);
	float vertices[] = {
		-6.0f, 6.0f,
		-6.0f, -5.55f,
		19.9f, 6.0f,
		19.9f, 6.0f,
		-6.0f, -5.55f,
		19.9f, -5.55f };

	glVertexAttribPointer(untexture.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(untexture.positionAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	// ========================================================================

	for (int i = 0; i < this->state->grass.size(); i++) {
		this->state->modelMatrix.SetPosition(this->state->grass[i].position.x, this->state->grass[i].position.y, 0);
		program.SetModelMatrix(this->state->modelMatrix);
		this->state->grass[i].DrawSpriteSheetSprite(program, this->state->grass[i].mapData, 16, 8, .3f);
	}

	// ==================================================================================
	// this->state->player render
	/*
	if (this->state->player.collidedBottom == false) {
		this->state->viewMatrix.Translate(sin(this->screenShakeValue * 20.0f) * 0.2f, 0.0f, 0.0f);
	}
	*/
	this->state->player.render(&program, this->state->modelMatrix, this->state->runAnimation, this->state->currentIndex);
	this->state->boss.render(&program);

	/*
	for (int i = 0; i < this->state->particles.size(); i++) {
	this->state->particles[i].Render(program);
	}
	*/

	// Bullets Render
	for (int i = 0; i < MAX_BULLETS; i++) {
		this->state->bullets[i].Draw(&program, this->state->modelMatrix);
	}

	for (int i = 0; i < MAX_BIGBULLETS; i++) {
		this->state->bigBullets[i].Drawful(&program);
	}

	for (int i = 0; i < this->state->enemies.size(); i++) {
		this->state->enemies[i].render(&program);
	}
}