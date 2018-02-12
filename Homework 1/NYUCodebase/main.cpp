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


SDL_Window* displayWindow;

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

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
	#ifdef _WINDOWS
		glewInit();
	#endif

	/* Setup Before Loop */
	glViewport(0, 0, 640, 360);
	ShaderProgram program;
	ShaderProgram textured;
	program.Load(RESOURCE_FOLDER"vertex.glsl", RESOURCE_FOLDER"fragment.glsl"); // Untextured
	textured.Load(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl"); // Textured

	GLuint emoji = LoadTexture(RESOURCE_FOLDER"background.png");
	GLuint plane = LoadTexture(RESOURCE_FOLDER"planeRed1.png");
	GLuint medal = LoadTexture(RESOURCE_FOLDER"shaded_medal6.png");

	Matrix projectionMatrix;

	Matrix modelMatrix;
	Matrix modelMatrixTex;
	Matrix modelMatrixPlane;
	Matrix modelMatrixMedal;
	modelMatrixTex.Scale(3.0f, 3.0f, 1.0f);

	modelMatrix.Translate(2.5f, 0.0f, 0.0f);

	float distance = -2.5f;
	modelMatrixPlane.Translate(-2.5f, 0.0f, 0.0f);

	modelMatrixMedal.Scale(.5f, .5f, 1.0f);
	modelMatrixMedal.Translate(5.25f, 0.0f, 0.0f);

	Matrix viewMatrix;

	float aspect = 640.0f / 360.0f; // 1.777777
	projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Animations

	float lastFrameTicks = 0.0f;

	glUseProgram(program.programID);
	glUseProgram(textured.programID);

	//modelMatrix.Translate(-1.0f, 0.0f, 0.0f); // translating
	//modelMatrix.Scale(3.0f, 3.0f, 1.0f); // scaling
	//modelMatrix.Rotate(45.0f * (3.14f / 180.0f)); // rotating

	//float = positionX = 0.0f;
	//float = positionY = 0.0f;


	SDL_Event event;
	bool done = false;
	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
			// This is the event type of input. If pressed space then it does something.
			/* else if (event.type ==SDL_KEYDOWN) 
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) 
				{
					positionX = 0.0f;
					positionY - 0.0f;
				}
			}*/
		}
		glClear(GL_COLOR_BUFFER_BIT);

		// Loop Time

		float ticks = (float)SDL_GetTicks()/1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		// Background # texture 1

		textured.SetModelMatrix(modelMatrixTex);
		textured.SetProjectionMatrix(projectionMatrix);
		textured.SetViewMatrix(viewMatrix);

		glBindTexture(GL_TEXTURE_2D, emoji);
		float vertices_emo[] = {-1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0}; // emoji
		glVertexAttribPointer(textured.positionAttribute, 2, GL_FLOAT, false, 0, vertices_emo);
		glEnableVertexAttribArray(textured.positionAttribute);

		float texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0};
		glVertexAttribPointer(textured.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(textured.texCoordAttribute);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(textured.positionAttribute);
		glDisableVertexAttribArray(textured.texCoordAttribute);
		
		// Plane # texture 2 and animated

		if (distance < 2.00) {
			distance += (elapsed * .5f);
			modelMatrixPlane.SetPosition(distance, 0.0f, 0.0f);
			textured.SetModelMatrix(modelMatrixPlane);
			glBindTexture(GL_TEXTURE_2D, plane);
			float vertices_plane[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
			glVertexAttribPointer(textured.positionAttribute, 2, GL_FLOAT, false, 0, vertices_plane);
			glEnableVertexAttribArray(textured.positionAttribute);

			float planeCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
			glVertexAttribPointer(textured.texCoordAttribute, 2, GL_FLOAT, false, 0, planeCoords);
			glEnableVertexAttribArray(textured.texCoordAttribute);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(textured.positionAttribute);
			glDisableVertexAttribArray(textured.texCoordAttribute);

			// Green Square # untextured
			program.SetModelMatrix(modelMatrix);
			program.SetProjectionMatrix(projectionMatrix);
			program.SetViewMatrix(viewMatrix);
			program.SetColor(0.2f, 0.8f, 0.4f, 1.0f);

			float vertices[] = { 0, -0.5, 0.5, -0.5, 0.5, 0.5, 0, -0.5, 0.5, 0.5, 0, 0.5 }; // Square
			glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
			glEnableVertexAttribArray(program.positionAttribute);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(program.positionAttribute);

			// Medal # texture

			textured.SetModelMatrix(modelMatrixMedal);
			glBindTexture(GL_TEXTURE_2D, medal);
			float vertices_medal[] = { 0, -0.5, 0.5, -0.5, 0.5, 0.5, 0, -0.5, 0.5, 0.5, 0, 0.5 };
			glVertexAttribPointer(textured.positionAttribute, 2, GL_FLOAT, false, 0, vertices_medal);
			glEnableVertexAttribArray(textured.positionAttribute);

			//float planeCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
			glVertexAttribPointer(textured.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
			glEnableVertexAttribArray(textured.texCoordAttribute);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(textured.positionAttribute);
			glDisableVertexAttribArray(textured.texCoordAttribute);
		}
		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}
