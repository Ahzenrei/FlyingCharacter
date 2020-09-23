#pragma once
#include "Vec2.h"
#include <math.h>
#include "World.h"

class Projectile
{
public:
	Projectile() = default;
	Projectile(const int _posX, const int _posY)
		:
		posX(_posX),
		posY(_posY),
		valid(true)
	{}

	bool isValid() const noexcept
	{
		return valid;
	}

	void setValid(const bool isValid)
	{
		valid = isValid;
	}

	int getX() const noexcept
	{
		return posX;
	}

	int getY() const noexcept
	{
		return posY;
	}
	
	void Spawn(const int x, const int y, const int vx, const int vy) noexcept
	{
		posX = x;
		posY = y;
		velocity.x = vx;
		velocity.y = vy;
	}

	void Move() noexcept
	{
		posX += velocity.x * speed;
		posY += velocity.y * speed;

		if (posX < 0 || posX >= SCREEN_WIDTH || posY < 0 || posY >= SCREEN_HEIGHT)
		{
			valid = false;
		}
	}

private:
	int posX = 0;
	int posY = 0;
	int speed = 2;
	bool valid = false;
	Vec2<int> velocity;

	
};

