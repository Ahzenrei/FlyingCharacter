#include "GameManager.h"
#include "Windows.h"

GameManager::GameManager()
{
    dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
    dwBufferCoord = { 0, 0 };
    rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
    new_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX );
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

void GameManager::ChangeFrame() noexcept
{
    player.ChangeFrame();
    for (Ennemy &ennemy : ennemies)
    {
        if (ennemy.IsValid())
        {
            ennemy.ChangeFrame();
        }
    }
}

void GameManager::SpawnEnnemy() noexcept
{

    for (Ennemy& ennemy : ennemies)
    {
        if (!ennemy.IsValid())
        {
            ennemy.Spawn(nextEnnemy);
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

    //Projectiles
    for (Projectile &projectile : player.projectiles)
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
                if (posX > SCREEN_WIDTH - 1 || posX < 0)
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

                    if (buffer[posY ][posX].Char.AsciiChar == '*') //Si on redessine par dessus un projectile alors l'ennemi est touché
                    {
                        ennemy.Kill();
                    }
                    buffer[posY][posX].Char.AsciiChar = ennemy.anim[ennemy.frame][i + ennemy.sizeX * j];
                    buffer[posY][posX].Attributes = ennemy.color;
                }
            }
        }
    }

    //Player

    if (player.facingLeft)
    {
        for (int i = 0; i < player.sizeX; i++)
        {
            for (int j = 0; j < player.sizeY; j++)
            {
                if (buffer[player.posY + j][player.posX + i].Char.AsciiChar != ' ' && buffer[player.posY + j][player.posX + i].Char.AsciiChar != '*')
                {
                    GameOver();
                }
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

void GameManager::GameOver() noexcept
{
    player.color = 0x08;
    //ded
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