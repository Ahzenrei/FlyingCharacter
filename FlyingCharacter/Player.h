#pragma once

#include "Vec2.h"

class Player
{
public:
	Player(int x, int y);
	void Move(Vec2<int>);
	Vec2<int> GetInput();
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

	const int color = 0x0E;
	const int sizeX = 4;
	const int sizeY = 6;
	bool frame = false;
	bool facingLeft = true;
	int posX;
	int posY;

private:
	int currentFrame = 0;
	const int frameToChange = 12;
};

