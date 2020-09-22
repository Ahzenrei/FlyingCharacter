#pragma once
#include "Player.h"
#include "NYTimer.h"
#include <memory>
#include <sstream>
#include "World.h"


class GameManager
{	
public:
	GameManager();
	void init();
	void WriteToConsole();
	void Flush();
private:
	LONG_PTR setConsoleWindowStyle(INT n_index);
	
public:
	NYTimer clock;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

private:
	COORD dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT rcRegion;
	LONG_PTR new_style;
	HANDLE hOutput;

};

