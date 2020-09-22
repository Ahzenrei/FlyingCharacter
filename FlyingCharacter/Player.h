#pragma once

#include "Vec2.h"

class Player
{
public:
	Player(int x, int y);
	void Move(Vec2<int>);
	Vec2<int> GetInput();

public:
	const char idleLeft[2][30] =
	{
		{
			'(' , ')' , ' ' , ' ' ,
			' ' , '(' , '[' , '\\',
			'/' , '(' , '[' , '|',
			' ' , '(' , 'V' , 'V',
			' ' , '|' , ' ' , '*',
			' ' , 'J' , '*' , ' '
	
		},
		{
			'(', ')', ' ', ' ',
			' ', '(', '[', '\\',
			'/', '(', '[', '|',
			' ', '(', 'V', 'V',
			' ', '|', '*', ' ',
			' ', 'J', ' ', '*'
	
		}
	};

	const int color = 0x0E;
	const int sizeX = 4;
	const int sizeY = 6;
	bool frame = false;
	int posX;
	int posY;
};

