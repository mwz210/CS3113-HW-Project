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
#include <vector>
#include "Square.h"
#include <math.h>

#define PI 3.14159265

int left_score = 0;
int right_score = 0;
float angle_x = (180.0f);
float angle_y = (180.0f);
bool done = false;

SDL_Window* displayWindow;

// For loading texture
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
	program.Load(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl");
	Matrix projectionMatrix;
	projectionMatrix.SetOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
	program.SetProjectionMatrix(projectionMatrix);
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ProcessEvents() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
	}
}

bool collision_detect(float* R1_sides, float* R2_sides)
{
	bool truth = false;
	if (R1_sides[1] > R2_sides[0] || R1_sides[0] < R2_sides[1] || R1_sides[3] > R2_sides[2] || R1_sides[2] < R2_sides[3])
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Update(ShaderProgram& program, float& lastFrameTicks, std::vector<float*> object, Square& puck)
{
	const Uint8 *key = SDL_GetKeyboardState(NULL);
	float ticks = (float)SDL_GetTicks() / 1000.0f;
	float elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	if (right_score > 5 || left_score > 5)
	{
		done = true;
	}

	if (puck.velocity_x >= 3.55f + (puck.width/2))
	{
		++right_score;
		puck.velocity_x = 0;
		puck.velocity_y = 0;
	}
	else if (puck.velocity_x < -3.55f - (puck.width/2))
	{
		++left_score;
		puck.velocity_x = 0;
		puck.velocity_y = 0;
	}

	if (key[SDL_SCANCODE_UP] && *object[1] < 1.20f)
	{
		*object[1] += elapsed * 2.0f;
	}
	else if (key[SDL_SCANCODE_DOWN] && *object[1] > -1.45f)
	{
		*object[1] -= elapsed * 2.0f;
	}
	if (key[SDL_SCANCODE_W] && *object[0] < 1.20f)
	{
		*object[0] += elapsed * 2.0f;
	}
	else if (key[SDL_SCANCODE_S] && *object[0] > -1.45f)
	{
		*object[0] -= elapsed * 2.0f;
	}
	//cos(45 * PI / 180.0)

	float puck_top = puck.velocity_y + (puck.height / 2);
	float puck_bottom = puck.velocity_y - (puck.height / 2);
	float puck_right = puck.velocity_x + (puck.width / 2);
	float puck_left = puck.velocity_x - (puck.width / 2);
	float object_1_top = *object[0] + 0.3;
	float object_1_bottom = *object[0] - 0.3;
	float object_1_right = -3.25f;
	float object_1_left = -3.55f;
	float object_2_top = *object[1] + 0.3;
	float object_2_bottom = *object[1] - 0.3;
	float object_2_right = 3.55f;
	float object_2_left = 3.25f;
	float border_1_top = 2.0f;
	float border_1_bottom = 1.5f;
	float border_1_right = 3.55f;
	float border_1_left = -3.55f;
	float border_2_top = -1.75f;
	float border_2_bottom = -2.0f;
	float border_2_right = 3.55f;
	float border_2_left = -3.55f;

	float doodle[] = { puck_top, puck_bottom, puck_right, puck_left };
	float object_1[] = { object_1_top, object_1_bottom, object_1_right, object_1_left };
	float object_2[] = { object_2_top, object_2_bottom, object_2_right, object_2_left };
	float border_1[] = { border_1_top, border_1_bottom, border_1_right, border_1_left };
	float border_2[] = { border_2_top, border_2_bottom, border_2_right, border_2_left };

	bool collision_1 = collision_detect(doodle, object_1);
	bool collision_2 = collision_detect(doodle, object_2);
	bool collision_3 = collision_detect(doodle, border_1);
	bool collision_4 = collision_detect(doodle, border_2);

	if (collision_1)
	{
		if (angle_x >= 90 && angle_y >= 90 && angle_x <= 180 && angle_y <= 180)
		{
			angle_x -= 45.0f;
			angle_y -= 45.0f;
		}
		else if (angle_x > 180 && angle_y > 180 && angle_x <= 270 && angle_y <= 270)
		{
			angle_x += 45.0f;
			angle_y += 45.0f;
		}
	}

	else if (collision_2)
	{
		if (angle_x <= 90 && angle_y <= 90 && angle_x >= 0 && angle_y >= 0)
		{
			angle_x += 45.0f;
			angle_y += 45.0f;
		}
		else if (angle_x >= 270 && angle_y >= 270 && angle_x <= 360 && angle_y <= 360)
		{
			angle_x -= 45.0f;
			angle_y -= 45.0f;
		}
	}

	else if (collision_3)
	{
		if (angle_x > 90 && angle_y > 90 && angle_x <= 180 && angle_y <= 180)
		{
			angle_x += 90;
			angle_y += 90;
		}
		else if (angle_x <= 90 && angle_y <= 90 && angle_x >= 0 && angle_y >= 0)
		{
			angle_x += 270;
			angle_y += 270;
		}
	}

	else if (collision_4)
	{
		if (angle_x >= 180 && angle_y >= 180 && angle_x < 270 && angle_y < 270)
		{
			angle_x -= 90;
			angle_y -= 90;
		}
		else if(angle_x <= 360 && angle_y <= 360 && angle_x >= 270 && angle_y >= 270)
		{
			angle_x -= 270;
			angle_y -= 270;
		}
	}

	puck.velocity_x += (cos(angle_x * PI/180.0f) * elapsed * 5.00f);
	puck.velocity_y += (sin(angle_y * PI/180.0f) * elapsed * 5.00f);
}

void Render(ShaderProgram& program, std::vector<float*> object, Square& puck)
{
	Matrix viewMatrix;
	Matrix modelMatrix;
	program.SetModelMatrix(modelMatrix);
	program.SetViewMatrix(viewMatrix);
	program.SetColor(1.0f, 0.0f, 0.0f, 1.0f);

	float vertices1[] = { -3.55f, 1.5f, -3.55f, 2.0f, 3.55f, 2.0f, -3.55f, 1.5f, 3.55f, 2.0f, 3.55f, 1.5f}; // Square
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices1);
	glEnableVertexAttribArray(program.positionAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	float vertices2[] = { -3.55f, -2.0f, -3.55f, -1.75f, 3.55f, -1.75f, -3.55f, -2.0f, 3.55f, -1.75f, 3.55f, -2.0f};
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices2);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	modelMatrix.SetPosition(0.0f, *object[0], 0.0f);
	program.SetModelMatrix(modelMatrix);
	float block1[] = { -3.55f, -0.3f, -3.55f, 0.3f, -3.25f, 0.3f, -3.55f, -0.3f, -3.25f, .3f, -3.25f, -.3f };
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, block1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	modelMatrix.SetPosition(0.0f, *object[1] , 0.0f);
	program.SetModelMatrix(modelMatrix);
	float block2[] = { 3.25f, -0.3f, 3.25f, 0.3f, 3.55f, 0.3f, 3.25f, -0.3f, 3.55f, 0.3f, 3.55f, -0.3f };
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, block2);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	puck.Draw(program);

	SDL_GL_SwapWindow(displayWindow);
}

void Cleanup(ShaderProgram& program)
{
	glDisableVertexAttribArray(program.positionAttribute);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	ShaderProgram program;
	Setup(program);
	float aspect = 640.0f / 360.0f; // 1.777777
	float lastFrameTicks = 0.0f;
	float block_one_y = 0.0f;
	float block_two_y = 0.0f;
	float block_three_y = 0.0f;
	std::vector<float*> object;
	object.push_back(&block_one_y);
	object.push_back(&block_two_y);
	object.push_back(&block_three_y);
	Square puck(program.programID, -0.1, 0.1, .2, .2, 0, 0);
	glUseProgram(program.programID);
	while (!done) {
		ProcessEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		Update(program, lastFrameTicks, object, puck);
		Render(program, object, puck);
	}
	Cleanup(program);
	return 0;
}
