#pragma once

#include <Windows.h>
#include <cwchar>
#include <chrono>
#include <thread>
#include "Pixel.h"

#define BLACK        0x0000 << 4
#define BLUE         0x0001 << 4
#define GREEN        0x0002 << 4
#define CYAN         0x0003 << 4
#define RED          0x0004 << 4
#define MAGENTA      0x0005 << 4
#define BROWN        0x0006 << 4
#define LIGHTGRAY    0x0007 << 4
#define DARKGRAY     0x0008 << 4
#define LIGHTBLUE    0x0009 << 4
#define LIGHTGREEN   0x000A << 4
#define LIGHTCYAN    0x000B << 4
#define LIGHTRED     0x000C << 4
#define LIGHTMAGENTA 0x000D << 4
#define YELLOW       0x000E << 4
#define WHITE        0x000F << 4

#define DARK         char(177)
#define NORMAL       ' ' 

class Screen //Screen is locked on 60 FPS value!
{
    Pixel* screenBuffer;
    Pixel* dirtyBuffer;

    HANDLE hConsole;
    DWORD bytesWritten;
    const int width;
    const int height;
    std::chrono::milliseconds frameDurationMs;



public:
    Screen(int nWidth, int nHeight);

    ~Screen();

    void displayScreen(bool clear);

    void setScreenActive();

    int setPixel(int x, int y, const Pixel& pixel); // TODO set pixel with browsed character and color

    void markAsDirty(int x, int y);

    int setPixel(int x, int y, WORD color); // set pixel to a space with browsed color

    void drawCircle(int centerX, int centerY, int radius, const Pixel& pixel);

    //getters, setters

    int getScreenWidth();

    int getScreenHeight();
};
