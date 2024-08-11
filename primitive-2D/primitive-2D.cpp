#include <iostream>
#include "Screen.h"



int main()
{
    Screen screen(320, 240); //generates 640x480 because of font size 2px
    screen.setScreenActive();

    int x = 160;
    int y = 120;
    bool toClear = false;
    Pixel drawPixel = Pixel{ MAGENTA, NORMAL };

    bool isWKeyPressed = false;

    while (true) {

        screen.displayScreen(toClear);


        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
           y--;
           screen.drawCircle(x, y, 2, drawPixel);
        }

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            x--;
            screen.drawCircle(x, y, 2, drawPixel);
        }

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            x++;
            screen.drawCircle(x, y, 2, drawPixel);
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            y++;
            screen.drawCircle(x, y, 2, drawPixel);
        }
    }
    

    return 0;
}