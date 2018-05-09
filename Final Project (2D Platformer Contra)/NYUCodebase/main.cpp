#ifdef _WINDOWS
	#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#ifdef _WINDOWS
	#define RESOURCE_FOLDER ""
#else
	#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

#define FIXED_TIMESTEP .0266666f
#define MAX_TIMESTEPS 6
#include "Matrix.h"
#include "ShaderProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <tuple>
#include <vector>
#include <string>
#include "GameState.h"
#include "GameMode.h"
#include "LevelOne.h"
#include "TitleScreen.h"
#include "Game_Over.h"
#include "LevelTwo.h"
#include <SDL_mixer.h>
#include "LevelThree.h"
#define MAX_BULLETS 5

SDL_Window* displayWindow;
ShaderProgram program;
ShaderProgram untexture;
GameState state;
LevelOne level_1;
LevelTwo level_2;
LevelThree level_3;
Game_Over game_ober;
TitleScreen titleScreen;
GameMode mode;
Mix_Music *background_music;

//Mix_Chunk *gun = Mix_LoadWAV("gun.wav");
int Mix_Open = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

GLuint LoadTexture(const char *filepath) 
{
	int w, h, comp;
	unsigned char* image = stbi_load(filepath, &w, &h, &comp, STBI_rgb_alpha);
	if (image == NULL)
	{
		std::cout << "Unable to load image. Make sure the path is correct\n";
		assert(false);
	}

	GLuint retTexture;
	glGenTextures(1, &retTexture);
	glBindTexture(GL_TEXTURE_2D, retTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(image);
	return retTexture;
}

void DrawSpriteSheetSprite(int index, int spriteCountX, int spriteCountY, float size) {
	if (index != 0) 
	{
		float u = (float)((int)index % spriteCountX) / (float)spriteCountX;
		float v = (float)((int)index / spriteCountX) / (float)spriteCountY;
		float spriteWidth = 1.0 / (float)spriteCountX;
		float spriteHeight = 1.0 / (float)spriteCountY;
		float aspect = 256.0 / 128.0;

		float vertices[] = {
			-0.5f * size, -0.5f * size,
			0.5f * size, 0.5 * size,
			-0.5f * size, 0.5f * size,
			0.5f * size, 0.5f * size,
			-0.5f * size, -0.5f * size,
			0.5f * size, -0.5f * size };

		glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program.positionAttribute);

		float texCoords[] = {
			u, v + spriteHeight,
			u + spriteWidth, v,
			u, v,
			u + spriteWidth, v,
			u, v + spriteHeight,
			u + spriteWidth, v + spriteHeight
		};
		glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program.texCoordAttribute);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

// ==============================================================================================================================================

// Testing point square collision
void TestingPointSquareCollision() {
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
	bottomSide[1] = state.player.position.y - .255f;
	bottomSide[0] = state.player.position.x;
	topSide[1] = state.player.position.y + .16f;
	topSide[0] = state.player.position.x;
	rightSide[1] = state.player.position.y;
	rightSide[0] = state.player.position.x + .15f;
	leftSide[1] = state.player.position.y;
	leftSide[0] = state.player.position.x - .15f;
	
	leftTopSide[0] = state.player.position.x - .15f;
	leftTopSide[1] = state.player.position.y + .11f;
	leftBottomSide[0] = state.player.position.x - .15f;
	leftBottomSide[1] = state.player.position.y - .20f;
	rightTopSide[0] = state.player.position.x + .15f ;
	rightTopSide[1] = state.player.position.y + .11f;
	rightBottomSide[0] = state.player.position.x + .15f;
	rightBottomSide[1] = state.player.position.y - .20f;

	// Traverse through solid blocks 
	for (int i = 0; i < state.grass.size(); i++) {
		float boxTop = state.grass[i].position.y + .15f;
		float boxBottom = state.grass[i].position.y - .15f;
		float boxRight = state.grass[i].position.x + .15f;
		float boxLeft = state.grass[i].position.x - .15f;

		// Logic for point and box collision. All points on player.
		if ((bottomSide[0] > boxLeft && bottomSide[0] < boxRight) && (bottomSide[1] > boxBottom && bottomSide[1] < boxTop)) {
			state.player.collidedBottom = true;
			float penetration = fabs((state.player.position.y - state.grass[i].position.y) - .255 - .15);
			state.player.position.y += penetration - 0.001;
		}
		if ((topSide[0] > boxLeft && topSide[0] < boxRight) && (topSide[1] > boxBottom && topSide[1] < boxTop)) {
			state.player.collidedTop = true;
			float penetration = fabs((state.grass[i].position.y - state.player.position.y) - .16 - .15);
			state.player.position.y -= penetration - 0.001;
		}
		if (((leftSide[0] > boxLeft && leftSide[0] < boxRight) && (leftSide[1] > boxBottom && leftSide[1] < boxTop)) || 
			((leftBottomSide[0] > boxLeft && leftBottomSide[0] < boxRight) && (leftBottomSide[1] > boxBottom && leftBottomSide[1] < boxTop)) ||
			((leftTopSide[0] > boxLeft && leftTopSide[0] < boxRight) && (leftTopSide[1] > boxBottom && leftTopSide[1] < boxTop))) {
			state.player.collidedLeft = true;
			float penetration = fabs((state.player.position.x - state.grass[i].position.x) - .15 - .15);
			state.player.position.x += penetration - 0.001;
		}
		if (((rightSide[0] > boxLeft && rightSide[0] < boxRight) && (rightSide[1] > boxBottom && rightSide[1] < boxTop)) ||
			((rightTopSide[0] > boxLeft && rightTopSide[0] < boxRight) && (rightTopSide[1] > boxBottom && rightTopSide[1] < boxTop)) ||
			((rightBottomSide[0] > boxLeft && rightBottomSide[0] < boxRight) && (rightBottomSide[1] > boxBottom && rightBottomSide[1] < boxTop))) {
			state.player.collidedRight = true;
			float penetration = fabs((state.grass[i].position.x - state.player.position.x) - .15 - .15);
			state.player.position.x -= penetration - 0.001;
		}
	}
}

void TestingCollisionWithBounce() {
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
	bottomSide[1] = state.player.position.y - .255f;
	bottomSide[0] = state.player.position.x;
	topSide[1] = state.player.position.y + .16f;
	topSide[0] = state.player.position.x;
	rightSide[1] = state.player.position.y;
	rightSide[0] = state.player.position.x + .15f;
	leftSide[1] = state.player.position.y;
	leftSide[0] = state.player.position.x - .15f;

	leftTopSide[0] = state.player.position.x - .15f;
	leftTopSide[1] = state.player.position.y + .11f;
	leftBottomSide[0] = state.player.position.x - .15f;
	leftBottomSide[1] = state.player.position.y - .20f;
	rightTopSide[0] = state.player.position.x + .15f;
	rightTopSide[1] = state.player.position.y + .11f;
	rightBottomSide[0] = state.player.position.x + .15f;
	rightBottomSide[1] = state.player.position.y - .20f;

	// Traverse through bounces
	for (int i = 0; i < state.bounces.size(); i++) {
		float boxTop = state.bounces[i].position.y + .08f;
		float boxBottom = state.bounces[i].position.y - .15f;
		float boxRight = state.bounces[i].position.x + .10f;
		float boxLeft = state.bounces[i].position.x - .10f;

		// Logic for point and box collision. All points on state.player.
		if ((bottomSide[0] > boxLeft && bottomSide[0] < boxRight) && (bottomSide[1] > boxBottom && bottomSide[1] < boxTop)) {
			state.player.collidedBottom = true;
			state.bounces[i].step = true;
			state.player.velocity.y = 2.0f;
		}
		if ((topSide[0] > boxLeft && topSide[0] < boxRight) && (topSide[1] > boxBottom && topSide[1] < boxTop)) {
			state.player.collidedTop = true;
			float penetration = fabs((state.bounces[i].position.y - state.player.position.y) - .16 - .15);
			state.player.position.y -= penetration - 0.001;
		}
		if (((leftSide[0] > boxLeft && leftSide[0] < boxRight) && (leftSide[1] > boxBottom && leftSide[1] < boxTop)) ||
			((leftBottomSide[0] > boxLeft && leftBottomSide[0] < boxRight) && (leftBottomSide[1] > boxBottom && leftBottomSide[1] < boxTop)) ||
			((leftTopSide[0] > boxLeft && leftTopSide[0] < boxRight) && (leftTopSide[1] > boxBottom && leftTopSide[1] < boxTop))) {
			state.player.collidedLeft = true;
			float penetration = fabs((state.player.position.x - state.bounces[i].position.x) - .15 - .10);
			state.player.position.x += penetration - 0.001;
		}
		if (((rightSide[0] > boxLeft && rightSide[0] < boxRight) && (rightSide[1] > boxBottom && rightSide[1] < boxTop)) ||
			((rightTopSide[0] > boxLeft && rightTopSide[0] < boxRight) && (rightTopSide[1] > boxBottom && rightTopSide[1] < boxTop)) ||
			((rightBottomSide[0] > boxLeft && rightBottomSide[0] < boxRight) && (rightBottomSide[1] > boxBottom && rightBottomSide[1] < boxTop))) {
			state.player.collidedRight = true;
			float penetration = fabs((state.bounces[i].position.x - state.player.position.x) - .15 - .10);
			state.player.position.x -= penetration - 0.001;
		}
	}
}

//=========================================================================================================================================
void Setup() 
{
	// Set up for SDL and Window
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif
	glViewport(0, 0, 640, 360);


	// Setup for program and mode
	program.Load(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl"); // Textured
	untexture.Load(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl");
	level_3.SetState(&state);
	level_2.SetState(&state);
	level_1.SetState(&state);
	titleScreen.SetMode(&mode);
	titleScreen.SetState(&state);
	level_1.SetMode(&mode);
	level_2.SetMode(&mode);
	level_3.SetMode(&mode);
	game_ober.SetMode(&mode);
	state.setup1("Scene_3.txt");

	// Setup for Matrix and Texture
	Matrix projectionMatrix;
	projectionMatrix.SetOrthoProjection(-4.80f, 5.30f, -4.80f, 5.30f, -1.0f, 1.0f);
	program.SetProjectionMatrix(projectionMatrix);
	untexture.SetProjectionMatrix(projectionMatrix);
	state.sprite = LoadTexture(RESOURCE_FOLDER"arne_sprites.png");
	GLuint fontTexture = LoadTexture(RESOURCE_FOLDER"font1.png");
	GLuint back = LoadTexture(RESOURCE_FOLDER"darkPurple.png");
	titleScreen.title.textureId = fontTexture;
	titleScreen.start.textureId = fontTexture;
	titleScreen.back.textureId = back;
	game_ober.title.textureId = fontTexture;
	game_ober.start.textureId = fontTexture;
	game_ober.back.textureId = back;
	background_music = Mix_LoadMUS("stage_one.wav");
	Mix_PlayMusic(background_music, -1);
	//Mix_PlayChannel(-1, gun, -1);
	// Initializing Enemies

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(program.programID);
	glUseProgram(untexture.programID);
}
void ProcessEvents(float elapsed) {

	switch (mode.mode) {
	case mode.STATE_TITLE_SCREEN:
		titleScreen.ProcessEvents(state.done, elapsed);
		break;
	case mode.STATE_GAME_LEVEL:
		level_1.ProcessEvents(elapsed);
		break;
	case mode.STATE_GAME_LEVEL_2:
		level_2.ProcessEvents(elapsed);
		break;
	case mode.STATE_GAME_LEVEL_3:
		level_3.ProcessEvents(elapsed);
		break;
	case mode.STATE_GAME_OVER:
		game_ober.ProcessEvents(state.done, elapsed);
		break;
	case mode.STATE_WIN_GAME:
		game_ober.ProcessEvents(state.done, elapsed);
		break;
	}
}
void Update(float elapsed) {
	switch (mode.mode) {
	case mode.STATE_TITLE_SCREEN:
		titleScreen.Update(program, elapsed);
		break;
	case mode.STATE_GAME_LEVEL:
		level_1.Update(elapsed);
		break;
	case mode.STATE_GAME_LEVEL_2:
		level_2.Update(elapsed);
		break;
	case mode.STATE_GAME_LEVEL_3:
		level_3.Update(elapsed);
		break;
	case mode.STATE_GAME_OVER:
		game_ober.Update(program, elapsed);
		break;
	case mode.STATE_WIN_GAME:
		game_ober.Update(program, elapsed);
		break;
	}
	
}
void Render() {
	switch (mode.mode) {
	case mode.STATE_TITLE_SCREEN:
		titleScreen.Render(program);
		break;
	case mode.STATE_GAME_LEVEL:
		level_1.Render(program, untexture);
		break;
	case mode.STATE_GAME_LEVEL_2:
		level_2.Render(program, untexture);
		break;
	case mode.STATE_GAME_LEVEL_3:
		level_3.Render(program, untexture);
		break;
	case mode.STATE_GAME_OVER:
		game_ober.Render(program);
		break;
	case mode.STATE_WIN_GAME:
		game_ober.Render(program);
		break;
	}
	
}
void Cleanup() {
	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);
	Mix_FreeMusic(background_music);	
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	Setup();
	while (!state.done) {
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - state.lastFrameTicks;
		state.lastFrameTicks = ticks;
		elapsed += state.accumulator;
		if (elapsed < FIXED_TIMESTEP) {
			state.accumulator = elapsed;
			continue;
		}
		while (elapsed >= FIXED_TIMESTEP) {
			Update(FIXED_TIMESTEP);
			elapsed -= FIXED_TIMESTEP;
		}
		state.accumulator = elapsed;
		ProcessEvents(elapsed);
		glClear(GL_COLOR_BUFFER_BIT);
		Render();
		SDL_GL_SwapWindow(displayWindow);
	}
	Cleanup();
	return 0;
}
