#pragma once
#include "Player.h"
#include "NYTimer.h"
#include <memory>
#include "World.h"


class GameManager
{	
public:
	GameManager();
	void init();
	void Input();
	void Flush();
	void WriteFrame();
	void Draw();

private:
	LONG_PTR setConsoleWindowStyle(INT n_index);
	
public:
	NYTimer clock;
	Player player;

private:
	COORD dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT rcRegion;
	LONG_PTR new_style;
	HANDLE hOutput;

	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

};

