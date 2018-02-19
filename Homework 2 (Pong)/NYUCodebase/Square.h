#include "ShaderProgram.h"

class Square {
	public:
		GLuint textureID;
		float velocity_x;
		float velocity_y;
		float width;
		float height;
		float x; 
		float y;
		Square(GLuint texID, float x, float y, float width, float height, float velocity_x, float velocity_y);
		void Draw(ShaderProgram &program);
};
