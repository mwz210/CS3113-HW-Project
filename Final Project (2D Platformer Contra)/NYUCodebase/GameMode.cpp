#include "GameMode.h"

GameMode::GameMode() {
	this->mode = STATE_TITLE_SCREEN;
}

void GameMode::change_mode(Game_Mode mod) {
	this->mode = mod;
}