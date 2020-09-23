#pragma once
#include "Player.h"
#include "Ennemy.h"
#include "NYTimer.h"
#include <memory>
#include "World.h"


class GameManager
{	
public:
	GameManager();
	void init();
	void Input() noexcept;
	void ChangeFrame() noexcept;
	void SpawnEnnemy() noexcept;
	void Move() noexcept;
	void Flush()noexcept;
	void WriteFrame() noexcept;
	void Draw();

private:
	LONG_PTR setConsoleWindowStyle(INT n_index);
	void GameOver() noexcept;
	
public:
	NYTimer clock;
	Player player;

private:
	COORD dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT rcRegion;
	LONG_PTR new_style;
	HANDLE hOutput;
	Ennemy ennemies[MAX_ENEMIES];
	char nextEnnemy = 0;
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

};

