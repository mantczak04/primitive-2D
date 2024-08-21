#pragma once
#include "Pixel.h"
#include <string>
#include <iostream>
#include "Screen.h"

class Sprite
{
	int width;
	int height;
	Pixel* pixels;
	std::string path;
public:
	Sprite(std::string path);
	~Sprite();
	void drawSprite(int x, int y, Screen& screen);
	
};