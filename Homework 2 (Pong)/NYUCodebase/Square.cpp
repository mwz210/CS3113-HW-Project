#include "Square.h"
#include "Matrix.h"

Square::Square(GLuint texID, float x, float y, float width, float height, float velocity_x, float velocity_y) : textureID(texID), x(x), y(y), width(width), height(height), velocity_x(velocity_x), velocity_y(velocity_y) {}

void Square::Draw(ShaderProgram& program)
{
	Matrix modelMatrix;
	modelMatrix.Translate(velocity_x, velocity_y, 0.0f);
	program.SetModelMatrix(modelMatrix);
	float bottom_y = y - height;
	float right_x = x + width;
	float vertice[] = { x, bottom_y, x, y, right_x, y, x, bottom_y, right_x, y, right_x, bottom_y };
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertice);
	glEnableVertexAttribArray(program.positionAttribute);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}