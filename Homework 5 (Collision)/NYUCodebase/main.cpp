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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "FlareMap.h"
#include "Player.h"
#include "SatCollision.h"
#include "Other.h"

bool done = false;
SDL_Window* displayWindow;
GLuint sprite;
float lastFrameTicks = 0.0f;
ShaderProgram program;
ShaderProgram untexture;
Matrix modelMatrix;
Matrix viewMatrix;
Player player;
Other object1;
Other object2;


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
/*
bool TestingCollision() {
	float playerSide[4];
	playerSide[0] = player.position.y + .2f;
	playerSide[1] = player.position.y - .2f;
	playerSide[2] = player.position.x + .2f;
	playerSide[3] = player.position.x - .2f;
	for (int i = 0; i < 128; i++) {
		float sides[4] = { grass[i].position.y + .2, grass[i].position.y - .2, grass[i].position.x + .2, grass[i].position.x - .2};
		if (player.square_collision_detect(playerSide, sides)) {
			return true;
		}
	}
	return false;
}
bool BossTestingCollision() {
	float bossSide[4];
	bossSide[0] = boss.position.y + 1.0f;
	bossSide[1] = boss.position.y - 1.0f;
	bossSide[2] = boss.position.x + 1.0f;
	bossSide[3] = boss.position.x - 1.0f;
	for (int i = 0; i < 128; i++) {
		float sides[4] = { grass[i].position.y + .2, grass[i].position.y - .2, grass[i].position.x + .2, grass[i].position.x - .2 };
		if (player.square_collision_detect(bossSide, sides)) {
			return true;
		}
	}
	return false;
}
void PlaceEntity(std::string type, float x, float y) {
	player.position.x = -5.67 + x;
	player.position.y = 5.65 + y;
}
*/


void Setup() 
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif
	glViewport(0, 0, 640, 360);
	program.Load(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl"); // Textured
	untexture.Load(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl");
	Matrix projectionMatrix;
	projectionMatrix.SetOrthoProjection(-6.00f, 6.00f, -6.00f, 6.00f, -1.0f, 1.0f);
	program.SetProjectionMatrix(projectionMatrix);
	untexture.SetProjectionMatrix(projectionMatrix);
	sprite = LoadTexture(RESOURCE_FOLDER"arne_sprites.png");
	glBindTexture(GL_TEXTURE_2D, sprite);

	object1.position.x = 4.00f;
	object1.model.SetRotation(PI / 6);

	object2.position.x = -4.00f;
	object2.model.SetRotation(PI / 2);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(program.programID);
	glUseProgram(untexture.programID);
}

void ProcessEvents(float elapsed) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}
}

void Update(float elapsed) {
	player.update(elapsed);
	object1.update(elapsed);
	object2.update(elapsed);
	std::vector<std::pair<float, float>> e1Points;
	std::vector<std::pair<float, float>> e2Points;
	std::vector<std::pair<float, float>> e3Points;
	std::pair<float, float> penetration;
	
	for (int i = 0; i < player.points.size(); i++) {
		Vector3 point = player.points[i] * player.model;
		e1Points.push_back(std::make_pair(point.x, point.y));
	}

	for (int i = 0; i < object1.points.size(); i++) {
		Vector3 point = object1.points[i] * object1.model;
		e2Points.push_back(std::make_pair(point.x, point.y));
	}
	
	for (int i = 0; i < object2.points.size(); i++) {
		Vector3 point = object2.points[i] * object2.model;
		e3Points.push_back(std::make_pair(point.x, point.y));
	}
	
	bool collided = CheckSATCollision(e1Points, e2Points, penetration);
	bool collided2 = CheckSATCollision(e1Points, e3Points, penetration);
	
	if (collided) {
		player.position.x += (penetration.first * 1.0f);
		player.position.y += (penetration.second * 1.0f);

		//object1.position.x -= (penetration.first * 0.5f);
		//object1.position.y -= (penetration.second * 0.5f);
	}
	if (collided2) {
		player.position.x += (penetration.first * 0.5f);
		player.position.y += (penetration.second * 0.5f);

		object2.position.x -= (penetration.first * 0.5f);
		object2.position.y -= (penetration.second * 0.5f);
	}

}

void Render() {
	// Background
	program.SetViewMatrix(viewMatrix);
	// ==================================================================================
	// player render
	player.render(&program);
	object1.render(&program);
	object2.render(&program);
	SDL_GL_SwapWindow(displayWindow);
}
void Cleanup() {
	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	Setup();
	while (!done) {
		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;
		ProcessEvents(elapsed);
		glClear(GL_COLOR_BUFFER_BIT);
		Update(elapsed);
		Render();
	}
	Cleanup();
	return 0;
}
