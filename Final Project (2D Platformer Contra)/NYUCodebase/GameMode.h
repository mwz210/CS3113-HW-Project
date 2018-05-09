#ifndef GAMEMODE_H
#define GAMEMODE_H

#pragma once

class GameMode {
public:
	enum Game_Mode { STATE_TITLE_SCREEN, STATE_GAME_LEVEL, STATE_GAME_OVER, STATE_GAME_LEVEL_2, STATE_GAME_LEVEL_3, STATE_WIN_GAME };
	Game_Mode mode;
	GameMode();
	void change_mode(Game_Mode mode);
};

#endif 