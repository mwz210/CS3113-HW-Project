#include "Background.h"

Background::Background() {}

void Background::SetSpriteSheet(SheetSprite sheet)
{
	sprite = sheet;
	size.x = sheet.size * 1 * (sheet.width / sheet.height);
	size.y = sheet.size * 1;
}

void Background::Draw(ShaderProgram *program, Matrix& model)
{
	model.SetPosition(this->position.x, this->position.y, this->position.z);
	program->SetModelMatrix(model);
	sprite.Draw(program);
}