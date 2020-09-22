#include "Player.h"
#include "Windows.h"
#include "World.h"

Player::Player(int x, int y)
	:
	posX(x),
	posY(y)
{}

void Player::Move(Vec2<int> velocity)
{
	posX += velocity.x;
	if (posX < 0)
	{
		posX = 0;
	}
	else if (posX >= SCREEN_WIDTH)
	{
		posX = SCREEN_WIDTH-1;
	}
	posY += velocity.y;
	if (posY < 0)
	{
		posY = 0;
	}
	else if (posY >= SCREEN_HEIGHT - sizeY)
	{
		posY = SCREEN_HEIGHT - sizeY - 1;
	}
}

Vec2<int> Player::GetInput()
{
	Vec2<int> velocity;
	if ((GetKeyState(0x51)) < 0)
	{
		velocity.x = -1;
	}
	else if ((GetKeyState(0x44)) < 0)
	{
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
	return velocity;

}

