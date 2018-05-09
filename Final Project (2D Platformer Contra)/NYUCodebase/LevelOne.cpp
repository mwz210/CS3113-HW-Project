#include "LevelOne.h"

/*
Mix_Chunk *coin = Mix_LoadWAV("coin.wav");
Mix_Chunk *jump = Mix_LoadWAV("jump.wav");
Mix_Chunk *death = Mix_LoadWAV("death.wav");

Mix_Music *gun = Mix_LoadMUS("gun.wav");
//Mix_Chunk *gun = Mix_LoadWAV("gun.wav");

int Mix_Open = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
*/

float mapValue(float value, float srcMin, float srcMax, float dstMin, float dstMax) {


	float retVal = dstMin + ((value - srcMin) / (srcMax - srcMin) * (dstMax - dstMin));
	if (retVal < dstMin) {
		retVal = dstMin;
	}
	if (retVal > dstMax) {
		retVal = dstMax;
	}
	return retVal;
}

float easeOut(float from, float to, float time) {
	float oneMinusT = 1.0f - time;
	float tVal = 1.0f - (oneMinusT * oneMinusT * oneMinusT * oneMinusT * oneMinusT);
	return (1.0f - tVal)*from + tVal * to;
}

bool square_collision_detect(float* R1_sides, float* R2_sides)
{
	return(!(R1_sides[0] < R2_sides[1] || R1_sides[1] > R2_sides[0] || R1_sides[2] < R2_sides[3] || R1_sides[3] > R2_sides[2]));
}

void LevelOne::TestingPointSquareCollision() {
	if (coin == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
	}

	if (jump == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
	}

	if (gun == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
	}

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
	
	// Traverse through vector of enemies and do point/box collision with solid object
	for (int j = 0; j < this->state->enemies.size(); j++) {

		float enemyTop = this->state->enemies[j].position.y + .15f;
		float enemyBottom = this->state->enemies[j].position.y - .15f;
		float enemyRight = this->state->enemies[j].position.x + .15f;
		float enemyLeft = this->state->enemies[j].position.x - .15f;
		

		bool isEmpty = true;
		
		// Checking all collision stuff 
		for (int i = 0; i < this->state->grass.size(); i++) {

			// Setting grass boxes
			float boxTop = this->state->grass[i].position.y + .15f;
			float boxBottom = this->state->grass[i].position.y - .15f;
			float boxRight = this->state->grass[i].position.x + .15f;
			float boxLeft = this->state->grass[i].position.x - .15f;

			// Collides with something on the left side
			if ((this->state->enemies[j].leftSide[0] > boxLeft &&
				this->state->enemies[j].leftSide[0] < boxRight) &&
				(this->state->enemies[j].leftSide[1] > boxBottom &&
					this->state->enemies[j].leftSide[1] < boxTop))
			{
				this->state->enemies[j].velocity.x *= -1.0f;
				this->state->enemies[j].direction = true;
				float penetration = fabs((this->state->enemies[j].position.x - this->state->grass[i].position.x) - .15 - .15);
				this->state->enemies[j].position.x += penetration + 0.01;
			}

			// Hits empty space on the left side
			else if ((this->state->enemies[j].farLeftSide[0] > boxLeft &&
				this->state->enemies[j].farLeftSide[0] < boxRight) &&
				(this->state->enemies[j].farLeftSide[1] > boxBottom &&
				this->state->enemies[j].farLeftSide[1] < boxTop)) {

				//this->state->enemies[j].position.y += 2.5f;

				isEmpty = false;

				//this->state->enemies[j].isMoving = "right";
			}
			
			// Collides with something on the right side 
			else if ((this->state->enemies[j].rightSide[0] > boxLeft &&
				this->state->enemies[j].rightSide[0] < boxRight) &&
				(this->state->enemies[j].rightSide[1] > boxBottom &&
				this->state->enemies[j].rightSide[1] < boxTop))
			{
				this->state->enemies[j].direction = false;
				float penetration = fabs((this->state->grass[i].position.x - this->state->enemies[j].position.x) - .15 - .15);
				this->state->enemies[j].position.x -= penetration + 0.01;
				this->state->enemies[j].velocity.x *= -1.0f;
			}

			else if ((this->state->enemies[j].farRightSide[0] > boxLeft &&
				this->state->enemies[j].farRightSide[0] < boxRight) &&
				(this->state->enemies[j].farRightSide[1] > boxBottom &&
					this->state->enemies[j].farRightSide[1] < boxTop)) {
				isEmpty = false;
			}

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
		
		// Traverse through bounces

		// What happens when the bug encounters empty air
		if (isEmpty) {
			this->state->enemies[j].velocity.x *= -1.0f;
			if (this->state->enemies[j].direction == false) {
				this->state->enemies[j].position.x += 0.05f;
				this->state->enemies[j].direction = true;
			}
			else {
				this->state->enemies[j].position.x -= 0.05f;
				this->state->enemies[j].direction = false;
			}
		}

		if ((bottomSide[0] > enemyLeft && bottomSide[0] < enemyRight) && (bottomSide[1] > enemyBottom && bottomSide[1] < enemyTop)) {
			this->state->player.exist = false;
			Mix_PlayChannel(-1, death, 0);
		}
		else if ((topSide[0] > enemyLeft && topSide[0] < enemyRight) && (topSide[1] > enemyBottom && topSide[1] < enemyTop)) {
			this->state->player.exist = false;
			Mix_PlayChannel(-1, death, 0);
		}
		else if (((leftSide[0] > enemyLeft && leftSide[0] < enemyRight) && (leftSide[1] > enemyBottom && leftSide[1] < enemyTop)) ||
			((leftBottomSide[0] > enemyLeft && leftBottomSide[0] < enemyRight) && (leftBottomSide[1] > enemyBottom && leftBottomSide[1] < enemyTop)) ||
			((leftTopSide[0] > enemyLeft && leftTopSide[0] < enemyRight) && (leftTopSide[1] > enemyBottom && leftTopSide[1] < enemyTop))) {
			this->state->player.exist = false;
			Mix_PlayChannel(-1, death, 0);
		}
		else if (((rightSide[0] > enemyLeft && rightSide[0] < enemyRight) && (rightSide[1] > enemyBottom && rightSide[1] < enemyTop)) ||
			((rightTopSide[0] > enemyLeft && rightTopSide[0] < enemyRight) && (rightTopSide[1] > enemyBottom && rightTopSide[1] < enemyTop)) ||
			((rightBottomSide[0] > enemyLeft && rightBottomSide[0] < enemyRight) && (rightBottomSide[1] > enemyBottom && rightBottomSide[1] < enemyTop))) {
			this->state->player.exist = false;
			Mix_PlayChannel(-1, death, 0);
		}
	}
	for (int i = 0; i < this->state->bounces.size(); i++) {
		float boxTop = this->state->bounces[i].position.y + .08f;
		float boxBottom = this->state->bounces[i].position.y - .15f;
		float boxRight = this->state->bounces[i].position.x + .10f;
		float boxLeft = this->state->bounces[i].position.x - .10f;

		// Logic for point and box collision. All points on this->state->player.
		if ((bottomSide[0] > boxLeft && bottomSide[0] < boxRight) && (bottomSide[1] > boxBottom && bottomSide[1] < boxTop)) {
			this->state->player.collidedBottom = true;
			this->state->bounces[i].step = true;
			this->state->player.velocity.y = 1.5f;
		}
		if ((topSide[0] > boxLeft && topSide[0] < boxRight) && (topSide[1] > boxBottom && topSide[1] < boxTop)) {
			this->state->player.collidedTop = true;
			float penetration = fabs((this->state->bounces[i].position.y - this->state->player.position.y) - .16 - .15);
			this->state->player.position.y -= penetration - 0.001;
		}
		if (((leftSide[0] > boxLeft && leftSide[0] < boxRight) && (leftSide[1] > boxBottom && leftSide[1] < boxTop)) ||
			((leftBottomSide[0] > boxLeft && leftBottomSide[0] < boxRight) && (leftBottomSide[1] > boxBottom && leftBottomSide[1] < boxTop)) ||
			((leftTopSide[0] > boxLeft && leftTopSide[0] < boxRight) && (leftTopSide[1] > boxBottom && leftTopSide[1] < boxTop))) {
			this->state->player.collidedLeft = true;
			float penetration = fabs((this->state->player.position.x - this->state->bounces[i].position.x) - .15 - .10);
			this->state->player.position.x += penetration - 0.001;
		}
		if (((rightSide[0] > boxLeft && rightSide[0] < boxRight) && (rightSide[1] > boxBottom && rightSide[1] < boxTop)) ||
			((rightTopSide[0] > boxLeft && rightTopSide[0] < boxRight) && (rightTopSide[1] > boxBottom && rightTopSide[1] < boxTop)) ||
			((rightBottomSide[0] > boxLeft && rightBottomSide[0] < boxRight) && (rightBottomSide[1] > boxBottom && rightBottomSide[1] < boxTop))) {
			this->state->player.collidedRight = true;
			float penetration = fabs((this->state->bounces[i].position.x - this->state->player.position.x) - .15 - .10);
			this->state->player.position.x -= penetration - 0.001;
		}
	}


	for (int i = 0; i < this->state->coins.size(); i++) {
		float boxTop = this->state->coins[i].position.y + .15f;
		float boxBottom = this->state->coins[i].position.y - .15f;
		float boxRight = this->state->coins[i].position.x + .15f;
		float boxLeft = this->state->coins[i].position.x - .15f;

		// Logic for point and box collision. All points on this->state->player.
		if ((bottomSide[0] > boxLeft && bottomSide[0] < boxRight) && (bottomSide[1] > boxBottom && bottomSide[1] < boxTop)) {
			this->state->coins[i].exist = false;
			this->state->player.coins += 1;
			Mix_PlayChannel(-1, coin, 0);
		}
		if ((topSide[0] > boxLeft && topSide[0] < boxRight) && (topSide[1] > boxBottom && topSide[1] < boxTop)) {
			this->state->coins[i].exist = false;
			this->state->player.coins += 1;
			Mix_PlayChannel(-1, coin, 0);
		}
		if (((leftSide[0] > boxLeft && leftSide[0] < boxRight) && (leftSide[1] > boxBottom && leftSide[1] < boxTop)) ||
			((leftBottomSide[0] > boxLeft && leftBottomSide[0] < boxRight) && (leftBottomSide[1] > boxBottom && leftBottomSide[1] < boxTop)) ||
			((leftTopSide[0] > boxLeft && leftTopSide[0] < boxRight) && (leftTopSide[1] > boxBottom && leftTopSide[1] < boxTop))) {
			this->state->coins[i].exist = false;
			this->state->player.coins += 1;
			Mix_PlayChannel(-1, coin, 0);
		}
		if (((rightSide[0] > boxLeft && rightSide[0] < boxRight) && (rightSide[1] > boxBottom && rightSide[1] < boxTop)) ||
			((rightTopSide[0] > boxLeft && rightTopSide[0] < boxRight) && (rightTopSide[1] > boxBottom && rightTopSide[1] < boxTop)) ||
			((rightBottomSide[0] > boxLeft && rightBottomSide[0] < boxRight) && (rightBottomSide[1] > boxBottom && rightBottomSide[1] < boxTop))) {
			this->state->coins[i].exist = false;
			this->state->player.coins += 1;
			Mix_PlayChannel(-1, coin, 0);
		}
	}


	// Traverse through solid blocks 
}

void LevelOne::TestingBulletCollision() {

	for (int i = 0; i < this->max_bullets; i++) {
		float bullet_sides[4] =
		{ this->state->bullets[i].position.y + .15,
			this->state->bullets[i].position.y - .15,
			this->state->bullets[i].position.x + .15,
			this->state->bullets[i].position.x - .15 };
		for (int j = 0; j < this->state->enemies.size(); j++)
		{
			float enemy_sides[4] =
			{
				this->state->enemies[j].position.y + .15,
				this->state->enemies[j].position.y - .15,
				this->state->enemies[j].position.x + .15,
				this->state->enemies[j].position.x - .15
			};
			if (this->state->enemies[j].square_collision_detect(enemy_sides, bullet_sides)) {
				this->state->enemies[j].exist = false;
				Mix_PlayChannel(-1, death, 0);
			}
		}
		
	}
}

void LevelOne::SetMode(GameMode* mode) {
	this->mode = mode;
}

void LevelOne::SetState(GameState* game_state) {
	this->state = game_state;
}

void LevelOne::ProcessEvents(float elapsed) {
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
					Mix_PlayChannel(-1, jump, -1);
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_Z) {
				if (this->state->bullets[this->state->bulletIndex].position.x > 100.0f) {
					this->state->player.ShootBullets(this->state->bullets[this->state->bulletIndex], elapsed);
					Mix_PlayMusic(gun, -1);
					//Mix_FadeInMusic(-1, gun, -1, 0);
					this->state->bulletIndex += 1;
					if (this->state->bulletIndex > MAX_BULLETS - 1) {
						this->state->bulletIndex = 0;
					}
				}
			}
		}
	}
}

void LevelOne::Update(float elapsed) {
	/*
	float bossSide[4];
	bossSide[0] = boss.position.y + 1.0f;
	bossSide[1] = boss.position.y - 1.0f;
	bossSide[2] = boss.position.x + .5f;
	bossSide[3] = boss.position.x - .5f;
	*/
	//this->screenShakeValue += elapsed;
	this->state->animationElapsed += elapsed;
	this->state->animationElapsedCoin += elapsed;
	if (this->state->player.position.x >= 76.80f - 10.80f) {
		this->mode->change_mode(mode->STATE_GAME_LEVEL_2);
		this->state->reset1();
		this->state->setup1("Scene_2.txt");
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

	for (int i = 0; i < this->state->bounces.size(); i++) {
		this->state->bounces[i].update(elapsed);
	}
	for (int i = 0; i < this->state->enemies.size(); i++) {
		this->state->enemies[i].update(elapsed);
	}

	/*
	bool coll;
	int index;
	std::tie(coll, index) = TestingSquareCollision();

	if (coll) {
	player.collidedBottom = true;
	float penetration = fabs((player.position.y - grass[index].position.y) - .15 - .15);
	player.position.y += penetration - 0.001;
	}
	*/

	/*
	if (BossTestingCollision()) {
	boss.collidedBottom = true;
	float penetration = fabs((boss.position.y - grass[0].position.y) - .2 - 1);
	boss.position.y += penetration - 0.001;
	}

	if (boss.square_collision_detect(bossSide, playerSide)) {
	player.exist = false;
	}
	*/
	for (int i = 0; i < MAX_BULLETS; i++) {
		this->state->bullets[i].update(elapsed);
	}

	state->player.update(elapsed);
	
	for (int i = 0; i < this->state->particles.size(); i++) {
		this->state->particles[i].Update(elapsed);
	}
	/*
	int v1 = rand() % 1000;
	if (boss.collidedBottom == true && v1 == 5) {
	boss.velocity.y = 1.0f;
	}
	*/
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

void LevelOne::Render(ShaderProgram& program, ShaderProgram& untexture) {
	if (this->state->player.exist == false && this->state->player.death <= 0) {
		this->state->reset1();
		this->mode->change_mode(mode->STATE_GAME_OVER);
	}
	// Background
	glBindTexture(GL_TEXTURE_2D, this->state->sprite);
	if (this->state->player.position.x > 0 && this->state->player.position.x < 76.80f) {
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
	this->state->player.render(&program, this->state->modelMatrix, this->state->runAnimation, this->state->currentIndex);
	
	/*
	for (int i = 0; i < this->state->particles.size(); i++) {
		this->state->particles[i].Render(program);
	}
	*/

	for (int i = 0; i < this->state->coins.size(); i++) {
		this->state->coins[i].Render(&program, this->state->runAnimationCoin, this->state->currentIndexCoin);
	}

	for (int i = 0; i < this->state->bounces.size(); i++) {
		this->state->bounces[i].Render(&program);
	}

	// Bullets Render
	for (int i = 0; i < MAX_BULLETS; i++) {
		this->state->bullets[i].Draw(&program, this->state->modelMatrix);
	}

	for (int i = 0; i < this->state->enemies.size(); i++) {
		this->state->enemies[i].render(&program);
	}
}