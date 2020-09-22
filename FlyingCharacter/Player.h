#pragma once
#include "Vec2.h"
#include "Projectile.h"
#include "World.h"

class Player
{
public:
	Player();
	Player(int x, int y);
	void Move();
	void Shoot();
	void ChangeFrame();

public:
	const char idleLeft[2][30] =
	{
		{
			'(' , ')' , ' ' , ' ' ,
			' ' , '(' , '[' , '\\',
			'/' , '(' , '[' , '|',
			' ' , '(' , 'V' , 'V',
			' ' , '|' , ' ' , '/',
			' ' , 'J' , '/' , ' '
	
		},
		{
			'(', ')', ' ', ' ',
			' ', '(', '[', '\\',
			'/', '(', '[', '|',
			' ', '(', 'V', 'V',
			' ', '/', ' ', '|',
			'/', ' ', ' ', 'J'
	
		}
	};

	const char idleRight[2][30] =
	{
		{
			' ' , ' ' , '(' , ')' ,
			'/' , ']' , ')' , ' ',
			'|' , ']' , ')' , '\\',
			'V' , 'V' , ')' , ' ',
			'\\' , ' ' , '|' , ' ',
			' ' , '\\' , 'L' , ' '

		},
		{
			' ' , ' ' , '(' , ')' ,
			'/' , ']' , ')' , ' ',
			'|' , ']' , ')' , '\\',
			'V' , 'V' , ')' , ' ',
			'|' , ' ' , '\\' , ' ',
			'L' , ' ' , ' ' , '\\'

		}
	};

	const int projectileColor = 0x0B;
	const char projectileFrame = '*';
	const int color = 0x0E;
	const int sizeX = 4;
	const int sizeY = 6;
	bool frame = false;
	bool facingLeft = true;

	int posX;
	int posY;
	Projectile projectiles[MAX_PROJECTILES];
	Vec2<int> velocity;

private:
	int currentFrame = 0;
	const int frameToChange = 12;
	int shooting = -1;
	const int shootingRecovery = 2;
};

