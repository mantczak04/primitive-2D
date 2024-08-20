#pragma once

#include "Screen.h"

class Player
{
	Screen screen;


public:
	int x;
	int y;

	Player(int nX, int nY, Screen screen);
	~Player();
	void setPos(int x, int y);
};

