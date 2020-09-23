#include "Player.h"
#include "Windows.h"


Player::Player()
{
	posX = SCREEN_WIDTH / 2;
	posY = SCREEN_HEIGHT / 2;
}

Player::Player(int x, int y)
	:
	posX(x),
	posY(y)
{}

void Player::Move()
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

void Player::Shoot()
{
	if (shooting != -1)
	{
		return;
	}

	shooting++;

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (!projectiles[i].isValid())
		{
			projectiles[i].setValid(true);

			if (velocity.x == 0 && velocity.y == 0) //If the player don't move he shoots in front of him
			{
				if (facingLeft)
				{
					projectiles[i].Spawn(posX, posY + 1, -1, 0);
				}
				else
				{
					projectiles[i].Spawn(posX, posY + 1, 1, 0);
				}
			}
			else //if he moves, he shoots in the direction he's going to
			{
				projectiles[i].Spawn(posX, posY + 1, velocity.x, velocity.y);
			}
	
			break;
		}
	}
}

void Player::ChangeFrame()
{
	//Handle Shooting
	if (shooting != -1)
	{
		shooting++;
	}
	if (shooting >= shootingRecovery)
	{
		shooting = -1;
	}

	//Handle changing frame
	currentFrame++;
	if (currentFrame >= frameToChange)
	{
		currentFrame = 0;
		frame = !frame;
	}

}

