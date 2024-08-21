#include "Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Sprite::Sprite(std::string sPath) : path(sPath) {
	int nWidth, nHeight, nChannels;
	unsigned char* image = stbi_load(sPath.c_str(), &nWidth, &nHeight, &nChannels, 0);

	if (image) {
		std::cout << "Image loaded " << sPath << std::endl;
		std::cout << "Width : " << nWidth << " " << nHeight << std::endl;
	}
	else {
		std::cout << "Can't get image for sprite";
	}
	width = nWidth;
	height = nHeight;

	pixels = new Pixel[width * height];

	//setup the pixels before getting the sprite
	for (int i = 0; i < width * height; i++) {
		pixels[i].color = BLACK;
		pixels[i].hue = NORMAL;
	}


	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = (y * width + x) * 4;

			unsigned char r = image[index];
			unsigned char g = image[index + 1];
			unsigned char b = image[index + 2];
			unsigned char a = image[index + 3];
		}
	}

	//pixels = new Pixel[width * height];
}

void Sprite::drawSprite(int x, int y, Screen& screen) {
	Pixel pixel = { RED, NORMAL };

	for (int i = x; i < width + x; i++) {
		for (int j = y; j < height + y; j++) {
			screen.setPixel(i, j, pixel);
		}
	}

}

Sprite::~Sprite() {
	delete[] pixels;
}