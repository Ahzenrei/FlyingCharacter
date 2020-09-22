#include "GameManager.h"
#include "Windows.h"

GameManager::GameManager()
{
    dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    dwBufferCoord = { 0, 0 };
    rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
    new_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX );
    hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
}

void GameManager::init()
{
	setConsoleWindowStyle(GWL_STYLE);

	clock.start();

    ReadConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
        dwBufferCoord, &rcRegion);
}

void GameManager::Input()
{

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

void GameManager::Flush()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            buffer[j][i].Char.AsciiChar = ' ';
        }
    }
}

void GameManager::WriteFrame() // Warning buffer is [Y][X]
{

    //Projectiles
    for (Projectile &projectile : player.projectiles)
    {
        if (projectile.isValid())
        {
            buffer[projectile.getY()][projectile.getX()].Char.AsciiChar = player.projectileFrame;
            buffer[projectile.getY()][projectile.getX()].Attributes = player.projectileColor;
        }
    }

    //Player

    if (player.facingLeft)
    {
        for (int i = 0; i < player.sizeX; i++)
        {
            for (int j = 0; j < player.sizeY; j++)
            {
                buffer[player.posY + j][player.posX + i].Char.AsciiChar = player.idleLeft[player.frame][i + player.sizeX * j];
                buffer[player.posY + j][player.posX + i].Attributes = player.color;
            }
        }
    }
    else
    {
        for (int i = 0; i < player.sizeX; i++)
        {
            for (int j = 0; j < player.sizeY; j++)
            {
                buffer[player.posY + j][player.posX + i].Char.AsciiChar = player.idleRight[player.frame][i + player.sizeX * j];
                buffer[player.posY + j][player.posX + i].Attributes = player.color;
            }
        }
    }
}

void GameManager::Draw()
{
    WriteConsoleOutput(hOutput, (CHAR_INFO*)buffer, dwBufferSize,
        dwBufferCoord, &rcRegion);
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