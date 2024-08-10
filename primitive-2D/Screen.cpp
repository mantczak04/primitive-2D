#include "Screen.h"

Screen::Screen(int nWidth, int nHeight)
    : width(nWidth), height(nHeight), bytesWritten(0), frameDurationMs(1000 / 60) // FPS = 60
{
    screen = new CHAR_INFO[width * height];

    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);

    // Inicjalizuj oba bufory z domyœlnymi wartoœciami
    for (int i = 0; i < width * height; ++i)
    {
        screen[i].Char.AsciiChar = DARK;
        screen[i].Attributes = RED;
    }
}

Screen::~Screen()
{
    delete[] screen;
    CloseHandle(hConsole);
}

void Screen::displayScreen()
{
    static auto lastFrameTime = std::chrono::high_resolution_clock::now(); // get last frame time

    SMALL_RECT writeRegion = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    WriteConsoleOutputA(hConsole, screen, bufferSize, {0,0}, &writeRegion);
    

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

int Screen::setPixel(int x, int y, WORD color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        int index = y * width + x;
        screen[index].Char.AsciiChar = ' ';
        screen[index].Attributes = color;
    }
    else return 100;
}


void Screen::drawCircle(int centerX, int centerY, int radius, WORD color)
{
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

    while (y <= x) {
        setPixel(centerX + x, centerY + y, color); // Octant 1
        setPixel(centerX + y, centerY + x, color); // Octant 2
        setPixel(centerX - y, centerY + x, color); // Octant 3
        setPixel(centerX - x, centerY + y, color); // Octant 4
        setPixel(centerX - x, centerY - y, color); // Octant 5
        setPixel(centerX - y, centerY - x, color); // Octant 6
        setPixel(centerX + y, centerY - x, color); // Octant 7
        setPixel(centerX + x, centerY - y, color); // Octant 8
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
