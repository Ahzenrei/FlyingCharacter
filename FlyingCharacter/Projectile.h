#pragma once
#include "Vec2.h"
#include <math.h>
#include "World.h"

class Projectile
{
public:
	Projectile() = default;
	Projectile(int _posX, int _posY)
		:
		posX(_posX),
		posY(_posY),
		valid(true)
	{}

	bool isValid()
	{
		return valid;
	}

	void setValid(bool isValid)
	{
		valid = isValid;
	}

	int getX()
	{
		return posX;
	}

	int getY()
	{
		return posY;
	}
	
	void Spawn(int x, int y, int vx, int vy)
	{
		posX = x;
		posY = y;
		velocity.x = vx;
		velocity.y = vy;
	}

	void Move()
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

