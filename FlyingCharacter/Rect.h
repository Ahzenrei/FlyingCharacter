#pragma once
class Rect
{
	Rect(int TL, int BR)
		:
		topLeft(TL),
		bottomRight(BR)
	{}

	int topLeft, bottomRight;
};