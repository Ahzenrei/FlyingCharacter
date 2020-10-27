#include "GameManager.h"
#include "Windows.h"
#include <string>

GameManager::GameManager()
{
	dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	dwBufferCoord = { 0, 0 };
	rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
	new_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void GameManager::init()
{
	setConsoleWindowStyle(GWL_STYLE);

	clock.start();
}

void GameManager::Input() noexcept
{
	if ((GetKeyState(VK_ESCAPE)) < 0)
	{
		exit(EXIT_SUCCESS);
	}

	//Starting the game
	if (gameState == GAME_STATE::START || gameState == GAME_STATE::GAMEOVER)
	{
		if ((GetKeyState(VK_RETURN)) < 0)
		{
			StartGame();
		}
		return;
	}

	//Shooting
	if ((GetKeyState(VK_SPACE)) < 0)
	{
		player.Shoot();
	}

	//Movement
	Vec2<int> velocity;

	if ((GetKeyState(0x51)) < 0)
	{
		player.facingLeft = true;
		velocity.x = -1;
	}
	else if ((GetKeyState(0x44)) < 0)
	{
		player.facingLeft = false;
		velocity.x = 1;
	}
	else
	{
		velocity.x = 0;
	}

	if (GetKeyState(0x5A) < 0)
	{
		velocity.y = -1;
	}
	else if (GetKeyState(0x53) < 0)
	{
		velocity.y = 1;
	}
	else
	{
		velocity.y = 0;
	}
	player.velocity = velocity;
}

void GameManager::Update() noexcept
{
	if (gameState == GAME_STATE::PLAYING) //Spawn an ennemy every frame
	{
		SpawnEnnemy();
		Move();
	}
	ChangeFrame();
}

void GameManager::ChangeFrame() noexcept
{
	if (gameState == GAME_STATE::PLAYING)
	{
		player.ChangeFrame();
		for (Ennemy& ennemy : ennemies)
		{
			if (ennemy.IsValid())
			{
				ennemy.ChangeFrame();
			}
		}
	}
	if (gameState == GAME_STATE::START)
	{
		//change frame for start screen if there is an animation
	}
	if (gameState == GAME_STATE::GAMEOVER)
	{
		//change frame for gameover screen if there is an animation
	}

}

void GameManager::StartGame() noexcept
{
	gameState = GAME_STATE::PLAYING;
	Reset();
}

void GameManager::SpawnEnnemy() noexcept
{
	for (int i = 0; i < nbEnnemies; i++)
	{
		if (!ennemies[i].IsValid())
		{
			ennemies[i].Spawn(nextEnnemy, difficulty);
			nextEnnemy = (nextEnnemy + 1) % 4;
			return;
		}
	}
}

void GameManager::Move() noexcept
{
	player.Move();

	for (Projectile& projectile : player.projectiles)
	{
		if (projectile.isValid())
		{
			projectile.Move();
		}
	}
	for (Ennemy& ennemy : ennemies)
	{
		if (ennemy.IsValid())
		{
			ennemy.MoveTo(player.posX, player.posY);
		}
	}
}

void GameManager::Flush() noexcept
{
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < SCREEN_HEIGHT; j++)
		{
			buffer[j][i].Char.AsciiChar = ' ';
		}
	}
}

void GameManager::WriteFrame() noexcept // Warning buffer is [Y][X]
{

	if (gameState == GAME_STATE::START)
	{
		//draw start screen
		char text[28] = "Welcome to pewpewland !"; 
		for (int i = 0; i < 28; i++) //we could do sizeof(text) / sizeof(char) to avoid hardcoded value but I'm lazy
		{
			buffer[SCREEN_HEIGHT / 2 - 1][SCREEN_WIDTH / 2 - 14 + i].Char.AsciiChar = text[i];
			buffer[SCREEN_HEIGHT / 2 - 1][SCREEN_WIDTH / 2 - 14 + i].Attributes = 0x02;
		}
		char text2[21] = "Press enter to start";
		for (int i = 0; i < 21; i++)
		{
			buffer[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2 - 14 + i].Char.AsciiChar = text2[i];
			buffer[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2 - 14 + i].Attributes = 0x02;
		}
		return;
	}

	if (gameState == GAME_STATE::GAMEOVER)
	{
		//draw game over screen
		std::string s = "You die ! your score : ";
		s += std::to_string(score);
		int size = s.size();
		for (int i = 0; i < size; i++)
		{
			buffer[SCREEN_HEIGHT / 2 - 1][SCREEN_WIDTH / 2 + i - size / 2].Char.AsciiChar = s[i];
			buffer[SCREEN_HEIGHT / 2 - 1][SCREEN_WIDTH / 2 + i - size / 2].Attributes = 0x02;
		}
		char text2[23] = "Press enter to restart";
		for (int i = 0; i < 23; i++)
		{
			buffer[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2 - size / 2 + i].Char.AsciiChar = text2[i];
			buffer[SCREEN_HEIGHT / 2][SCREEN_WIDTH / 2 - size / 2 + i].Attributes = 0x02;
		}
		return;
		return;
	}

	//Projectiles
	for (Projectile& projectile : player.projectiles)
	{
		if (projectile.isValid())
		{
			buffer[projectile.getY()][projectile.getX()].Char.AsciiChar = player.projectileFrame;
			buffer[projectile.getY()][projectile.getX()].Attributes = player.projectileColor;
		}
	}

	//Ennemies
	for (Ennemy& ennemy : ennemies)
	{
		if (ennemy.IsValid())
		{
			for (int i = 0; i < ennemy.sizeX; i++)
			{
				int posX = ennemy.posX + i;
				if (posX > SCREEN_WIDTH - 1 || posX < 0) //discard every characters that is out of the screen
				{
					continue;
				}

				for (int j = 0; j < ennemy.sizeY; j++)
				{

					int posY = ennemy.posY + j;

					if (posY > SCREEN_HEIGHT - 1 || posY < 0)
					{
						continue;
					}

					if (buffer[posY][posX].Char.AsciiChar == '*') //if we redraw onto a projectile, the ennemy dies
					{
						AddScore();
						ennemy.Kill();
					}
					buffer[posY][posX].Char.AsciiChar = ennemy.anim[ennemy.frame][i + ennemy.sizeX * j];
					buffer[posY][posX].Attributes = ennemy.color;
				}
			}
		}
	}

	//Player

	if (player.facingLeft) //draws the player facing left
	{
		for (int i = 0; i < player.sizeX; i++)
		{
			for (int j = 0; j < player.sizeY; j++)
			{
				if (buffer[player.posY + j][player.posX + i].Char.AsciiChar != ' ' && buffer[player.posY + j][player.posX + i].Char.AsciiChar != '*')
				{ //if we redraw the player onto something that is not a space or a projectile, then it's an ennemy so we die
					GameOver();
					return;
				}
				buffer[player.posY + j][player.posX + i].Char.AsciiChar = player.idleLeft[player.frame][i + player.sizeX * j];
				buffer[player.posY + j][player.posX + i].Attributes = player.color;
			}
		}
	}
	else //draws the player facing right
	{
		for (int i = 0; i < player.sizeX; i++)
		{
			for (int j = 0; j < player.sizeY; j++)
			{
				if (buffer[player.posY + j][player.posX + i].Char.AsciiChar != ' ' && buffer[player.posY + j][player.posX + i].Char.AsciiChar != '*')
				{ //if we write the player onto something that is not a space or a projectile, then it's an ennemy so we die
					GameOver();
					return;
				}
				buffer[player.posY + j][player.posX + i].Char.AsciiChar = player.idleRight[player.frame][i + player.sizeX * j];
				buffer[player.posY + j][player.posX + i].Attributes = player.color;
			}
		}
	}

	//Draw score
	std::string s = "Score: ";
	s += std::to_string(score);
	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		buffer[1][SCREEN_WIDTH + i - size - 2].Char.AsciiChar = s[i];
		buffer[1][SCREEN_WIDTH + i - size - 2].Attributes = 0x02;
	}
}

void GameManager::Draw()
{
	WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
		dwBufferCoord, &rcRegion);
}

void GameManager::GameOver() noexcept
{
	gameState = GAME_STATE::GAMEOVER;
}

void GameManager::Reset() noexcept //Replace the player in the center of the screen, reset the score and kill every ennemies/projectiles
{
	player.posX = SCREEN_WIDTH / 2;
	player.posY = SCREEN_HEIGHT / 2;
	score = 0;
	nbEnnemies = 3;
	difficulty = 1;
	for (Ennemy& ennemy : ennemies)
	{
		ennemy.Kill();
	}
	for (Projectile& projectile : player.projectiles)
	{
		projectile.setValid(false);
	}
}

void GameManager::AddScore() noexcept
{
	score++;
	if (score % (5 * (difficulty * difficulty)) == 0) //Increase difficulty every 5 * difficulty² points
	{
		difficulty++;
		nbEnnemies = (nbEnnemies + 1) < MAX_ENEMIES ? nbEnnemies + 1 : MAX_ENEMIES;
	}
}

LONG_PTR GameManager::setConsoleWindowStyle(INT n_index)
{
	/*The function does not clear the last error information. if last value was zero.*/
	SetLastError(NO_ERROR);

	HWND hwnd_console = GetConsoleWindow();
	LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, n_index, new_style);
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

	//show window after updating
	ShowWindow(hwnd_console, SW_SHOW);

	return style_ptr;
}