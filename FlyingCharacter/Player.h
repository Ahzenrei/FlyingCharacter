#pragma once
class Player
{
public:
	Player(int x, int y);
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
	int x;
	int y;
};

