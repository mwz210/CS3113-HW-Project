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

#include "Matrix.h"
#include "ShaderProgram.h"
#include "GameState.h"
#include "SheetSprite.h"
#include "GameLevel.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define MAX_BULLETS 10
#include <cstdlib>
#include "TitleScreen.h"
#include "GameMode.h"


SDL_Window* displayWindow;
GameState state;
GameMode mode;
GameLevel gameLevel;
TitleScreen titleScreen;
Mix_Music *background_music;
int Mix_Open = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

const Uint8 *key = SDL_GetKeyboardState(NULL);


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

void Setup(ShaderProgram& program)
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif
	glViewport(0, 0, 640, 360);
	program.Load(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");
	Matrix projectionMatrix;
	projectionMatrix.SetOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
	program.SetProjectionMatrix(projectionMatrix);
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	titleScreen.mode = &mode;
	GLuint planeTexture = LoadTexture(RESOURCE_FOLDER"plane.png");
	GLuint fontTexture = LoadTexture(RESOURCE_FOLDER"font1.png");
	GLuint back = LoadTexture(RESOURCE_FOLDER"darkPurple.png");
	state.initialize(planeTexture);
	gameLevel.state = state;
	titleScreen.title.textureId = fontTexture;
	titleScreen.back.textureId = back;
	titleScreen.start.textureId = fontTexture;
	gameLevel.state.scoreboard.textureId = fontTexture;
	background_music = Mix_LoadMUS("music.wav");
	Mix_PlayMusic(background_music, -1);
}
void ProcessInput(bool& done, float elapsed) {
	switch (mode.mode) {
	case mode.STATE_TITLE_SCREEN:
		titleScreen.ProcessEvents(done, elapsed);
		break;
	case mode.STATE_GAME_LEVEL:
		gameLevel.ProcessEvents(done, elapsed);
		break;
	}
}
void Update(ShaderProgram& program, float elapsed) {
	switch (mode.mode) {
	case mode.STATE_TITLE_SCREEN:
		titleScreen.Update(program, elapsed);
		break;
	case mode.STATE_GAME_LEVEL:
		gameLevel.Update(program, elapsed);
		break;
	}
}
void Render(ShaderProgram& program) {
	switch (mode.mode) {
		case mode.STATE_TITLE_SCREEN:
			titleScreen.Render(program);
			break;
		case mode.STATE_GAME_LEVEL:
			gameLevel.Render(program);
			break;
	}
}
void Cleanup(ShaderProgram& program)
{
	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);
	Mix_FreeMusic(background_music);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	ShaderProgram program;
	float lastFrameTicks = 0.0f;
	Setup(program);
	glUseProgram(program.programID);
	bool done = false;
	while (!done) {
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;
		ProcessInput(done, elapsed);
		glClear(GL_COLOR_BUFFER_BIT);
		Update(program, elapsed);
		Render(program);
		SDL_GL_SwapWindow(displayWindow);
	}
	Cleanup(program);
	return 0;
}


