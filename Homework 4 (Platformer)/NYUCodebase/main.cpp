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
#include "Enemy.h"
#include "Ground.h"
#include "Bullets.h"
#define MAX_BULLETS 10

bool done = false;
SDL_Window* displayWindow;
GLuint sprite;
float lastFrameTicks = 0.0f;
ShaderProgram program;
ShaderProgram untexture;
FlareMap map;
Matrix modelMatrix;
Matrix viewMatrix;
Matrix backModel;
Matrix backView;
Player player;
Enemy boss;
Ground grass[128];
Bullets bullets[MAX_BULLETS];
int bulletIndex = 0;


// Animation
const int runAnimation[] = { 80,81 };
const int numFrames = 2;
float animationElapsed = 0.0f;
float framesPerSecond = 10.0f;
int currentIndex = 0;

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

	// Initializing Bullets
	for (int i = 0; i < MAX_BULLETS; i++) {
		bullets[i].position.x = 2000.f;
	}

	// FlareMap
	map.Load("Project.txt");
	for (int i = 0; i < map.entities.size(); i++) {
		PlaceEntity(map.entities[i].type, (map.entities[i].x) * .4, (map.entities[i].y - 2) * -.4);
	}

	// Initializing Enemies
	boss.position.x = -5.67 + 10.0f;
	boss.position.y = player.position.y + 1.15;

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
		else if (event.type == SDL_KEYDOWN) {
			// Jump for Player
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				if (player.collidedBottom == true) {
					player.velocity.y = 1.0f;
				}
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_Z) {
				if (bullets[bulletIndex].position.x > 20.0f) {
					player.ShootBullets(bullets[bulletIndex], elapsed);
					bulletIndex += 1;
					if (bulletIndex > MAX_BULLETS - 1) {
						bulletIndex = 0;
					}
					
				}
			}
		}
	}
}

void Update(float elapsed) {
	float bossSide[4];
	bossSide[0] = boss.position.y + 1.0f;
	bossSide[1] = boss.position.y - 1.0f;
	bossSide[2] = boss.position.x + .5f;
	bossSide[3] = boss.position.x - .5f;

	float playerSide[4];
	playerSide[0] = player.position.y + .4f;
	playerSide[1] = player.position.y - .4f;
	playerSide[2] = player.position.x + .4f;
	playerSide[3] = player.position.x - .4f;

	animationElapsed += elapsed;

	player.reset_collision_flags();
	boss.reset_collision_flags();

	if (TestingCollision()) {
		player.collidedBottom = true;
		float penetration = fabs((player.position.y - grass[0].position.y) - .2 - .2);
		player.position.y += penetration - 0.001;
	}
	if (BossTestingCollision()) {
		boss.collidedBottom = true;
		float penetration = fabs((boss.position.y - grass[0].position.y) - .2 - 1);
		boss.position.y += penetration - 0.001;
	}
	if (boss.square_collision_detect(bossSide, playerSide)) {
		player.exist = false;
	}

	for (int i = 0; i < MAX_BULLETS; i++) {
		if (boss.square_collision_detect(bullets[i].sides, bossSide)) {
			boss.health -= 2;
			bullets[i].position.x = 2000.0f;
		}
		bullets[i].update(elapsed);
	}

	player.update(elapsed);
	boss.update(elapsed);

	int v1 = rand() % 1000;
	if (boss.collidedBottom == true && v1 == 5) {
		boss.velocity.y = 1.0f;
	}


	if (animationElapsed > 1.0 / framesPerSecond) {
		currentIndex++;
		animationElapsed = 0.0;
		if (currentIndex > numFrames - 1) {
			currentIndex = 0;
		}
	}
}

void Render() {
	// Background
	if (player.position.x > 0 && player.position.x < 51.20f - 12.10f) {
		viewMatrix.SetPosition(-player.position.x, 0, 0);
	}
	program.SetViewMatrix(viewMatrix);
	untexture.SetColor(0.0f, 0.749f, 1.0f, 1.0f);
	untexture.SetModelMatrix(backModel);
	untexture.SetViewMatrix(backView);
	float vertices[] = {
		-6.0f, 6.0f,
		-6.0f, -4.4f,
		19.9f, 6.0f,
		19.9f, 6.0f,
		-6.0f, -4.4f,
		19.9f, -4.4f };

	glVertexAttribPointer(untexture.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(untexture.positionAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	// ========================================================================

	// Making 2d Map
	float y_position = 5.67;
	float x_position = -5.65;
	modelMatrix.SetPosition(x_position, y_position, 0);

	// Traversing 2d array data
	for (int y = 3; y < map.mapHeight; y++) {
		for (int x = 0; x < map.mapWidth; x++) {
			program.SetModelMatrix(modelMatrix);
			if (y == 28) {
				grass[x].position.x = x_position;
				grass[x].position.y = y_position;
				grass[x].DrawSpriteSheetSprite(program, map.mapData[y][x], 16, 8, .4f);
			}
			else {
				if (map.mapData[y][x] > 300) {
					DrawSpriteSheetSprite(33, 16, 8, .4f);
				}
				else {
					DrawSpriteSheetSprite(map.mapData[y][x], 16, 8, .4f);
				}
			}
			x_position += .4;
			modelMatrix.SetPosition(x_position, y_position, 0);
		}
		x_position = -5.65;
		y_position -= .4f;
		modelMatrix.SetPosition(x_position, y_position, 0);
	}

	// ==================================================================================
	// player render
	player.render(&program, modelMatrix, runAnimation, currentIndex);
	boss.render(&program, modelMatrix);

	// Bullets Render
	for (int i = 0; i < MAX_BULLETS; i++) {
		bullets[i].Draw(&program, modelMatrix);
	}

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
