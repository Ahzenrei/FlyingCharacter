#pragma once
#include "Vec2.h"
#include "World.h"
#include <random>

class Ennemy
{
public:
	Ennemy() = default;
	Ennemy(int x, int y)
	{
		posX = x;
		posY = y;
		isValid = true;
	}

	void MoveTo(const int targetX, const int targetY) noexcept
	{
		if (moving > 0)
		{
			moving = (moving + 1)%frameToMove;
			return;
		}
		moving++;

		int directionX = targetX - posX;
		int directionY = targetY - posY;

		if (directionX != 0)
		{
			velocity.x = directionX < 0 ? -1 : 1;
		}
		else
		{
			velocity.x = 0;
		}
		if (directionY != 0)
		{
			velocity.y = directionY < 0 ? -1 : 1;
		}
		else
		{
			velocity.y = 0;
		}
		posX += velocity.x * speed;
		posY += velocity.y * speed;
	}

	void ChangeFrame() noexcept
	{
		currentFrame++;
		if (currentFrame >= frameToChange)
		{
			currentFrame = 0;
			frame = !frame;
		}
	}

	bool IsValid() const noexcept
	{
		return isValid;
	}

	void Spawn(char side) noexcept
	{
		std::random_device r;
		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist_width(0, SCREEN_WIDTH);
		std::uniform_int_distribution<int> uniform_dist_height(0, SCREEN_HEIGHT);	
		switch (side)
		{
			case 0: //Left side
				posX = 0;
				posY = uniform_dist_height(e1);
				break;
			case 1: //Top side
				posX = uniform_dist_width(e1);
				posY = 0;
				break;
			case 2: // Right side
				posX = SCREEN_WIDTH - 1;
				posY = uniform_dist_height(e1);
				break;
			case 3: //Bottom side
				posX = uniform_dist_width(e1);
				posY = SCREEN_HEIGHT - 1;
				break;
		}

		isValid = true;
	}

	void Kill() noexcept
	{
		isValid = false;
	}

public:

	const char anim[2][15] =
	{
		{
			' ' , '_'  , '_' , ' ' , ' ',
			'/' , '�'  , '_' , '�' , '\\',
			' ' , '\\' , '_' , '/' , ' '

		},
		{
			' ' , '_'  , '_' , ' ' , ' ',
			'/' , '.'  , '_' , '.' , '\\',
			' ' , '\\' , '_' , '/' , ' '

		}
	};

	const int color = 0x05;
	const int sizeX = 5;
	const int sizeY = 3;
	bool frame = false;
	bool facingLeft = true;

	int posX = -1;
	int posY = -1;
	Vec2<int> velocity;

private:
	int speed = 1;
	int currentFrame = 0;
	const int frameToChange = 12;
	int moving = 0;
	const int frameToMove = 2;
	bool isValid = false;
};