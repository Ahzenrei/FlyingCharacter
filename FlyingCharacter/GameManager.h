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
	void Update() noexcept;
	void Flush()noexcept;
	void WriteFrame() noexcept;
	void Draw();

private:
	LONG_PTR setConsoleWindowStyle(INT n_index);
	void ChangeFrame() noexcept;
	void StartGame() noexcept;
	void SpawnEnnemy() noexcept;
	void Move() noexcept;
	void GameOver() noexcept;
	void Reset() noexcept;
	void AddScore() noexcept;
	
public:
	enum class GAME_STATE { START, PLAYING, GAMEOVER };
	GAME_STATE gameState = GAME_STATE::START;
	NYTimer clock;
	Player player;

private:
	int score = 0;
	COORD dwBufferSize;
	COORD dwBufferCoord;
	SMALL_RECT rcRegion;
	LONG_PTR new_style;
	HANDLE hOutput;
	int nbEnnemies = 3;
	int difficulty = 1;
	Ennemy ennemies[MAX_ENEMIES];
	char nextEnnemy = 0; //Define which side the ennemy will spawn
	CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

};

