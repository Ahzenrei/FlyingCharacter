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
	else if (posX >= SCREEN_WIDTH - sizeX)
	{
		posX = SCREEN_WIDTH-1-sizeX;
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
		facingLeft = true;
		velocity.x = -1;
	}
	else if ((GetKeyState(0x44)) < 0)
	{
		facingLeft = false;
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

void Player::ChangeFrame()
{
	currentFrame++;
	if (currentFrame >= frameToChange)
	{
		currentFrame = 0;
		frame = !frame;
	}
}

