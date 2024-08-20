#include "Screen.h"

Screen::Screen(int nWidth, int nHeight)
    : width(nWidth), height(nHeight), bytesWritten(0), frameDurationMs(1000 / 60) // FPS = 60
{
    backBuffer = new Pixel[width * height];

    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);

    Pixel blankPixel;
    blankPixel.color = BLACK;
    blankPixel.hue = NORMAL;
    std::fill_n(backBuffer, width * height, blankPixel);
}

Screen::~Screen()
{
    delete[] backBuffer;
    CloseHandle(hConsole);
}

void Screen::clearBackBuffer()
{
    std::fill_n(backBuffer, width * height, Pixel{ BLACK, NORMAL });
}

void Screen::displayScreen()
{
    static auto lastFrameTime = std::chrono::high_resolution_clock::now(); // get last frame time

    SMALL_RECT writeRegion = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };


    CHAR_INFO* frontBuffer = new CHAR_INFO[width * height];

    for (int i = 0; i < width * height; ++i) {
        frontBuffer[i].Char.AsciiChar = backBuffer[i].hue;
        frontBuffer[i].Attributes = backBuffer[i].color;
    }

    WriteConsoleOutputA(hConsole, frontBuffer, bufferSize, {0,0}, &writeRegion);
    
    

    // calculate frame time
    auto currentFrameTime = std::chrono::high_resolution_clock::now(); // get current frame time
    std::chrono::duration<double, std::milli> frameDuration = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    //set wait time to next frame
    auto sleepDuration = frameDurationMs - frameDuration;

    if (sleepDuration.count() > 0)
    {
        std::this_thread::sleep_for(sleepDuration);
    }
    
}

void Screen::setScreenActive()
{
    SetConsoleActiveScreenBuffer(hConsole);
}

int Screen::setPixel(int x, int y, const Pixel& pixel)
{
    if (x >= 0 && x < width && y >= 0 && y < height) 
    {
        int index = y * width + x;
        backBuffer[index] = pixel;

    }
    else return 100;
}

void Screen::drawCircle(int centerX, int centerY, int radius, const Pixel& pixel) {
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

    while (y <= x) {
        setPixel(centerX + x, centerY + y, pixel); // Octant 1
        setPixel(centerX + y, centerY + x, pixel); // Octant 2
        setPixel(centerX - y, centerY + x, pixel); // Octant 3
        setPixel(centerX - x, centerY + y, pixel); // Octant 4
        setPixel(centerX - x, centerY - y, pixel); // Octant 5
        setPixel(centerX - y, centerY - x, pixel); // Octant 6
        setPixel(centerX + y, centerY - x, pixel); // Octant 7
        setPixel(centerX + x, centerY - y, pixel); // Octant 8
        y++;
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
        }
        else {
            x--;
            decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
        }
    }
}


int Screen::getScreenWidth()
{
    return width;
}

int Screen::getScreenHeight()
{
    return height;
}
