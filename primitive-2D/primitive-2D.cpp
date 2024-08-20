#include <iostream>
#include "Screen.h"
#include "Player.h"


int main()
{
    Screen screen(320, 240); //generates 640x480 because of font size 2px
    screen.setScreenActive();

    int x = 160;
    int y = 120;
    Pixel drawPixel = Pixel{ MAGENTA, NORMAL };


    while (true) {

        


        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
           screen.clearBackBuffer();
           y--;
           screen.drawCircle(x, y, 2, drawPixel);
           
        }

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
        {
            screen.clearBackBuffer();
            x--;
            screen.drawCircle(x, y, 2, drawPixel);
        }

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
        {
            screen.clearBackBuffer();
            x++;
            screen.drawCircle(x, y, 2, drawPixel);
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
        {
            screen.clearBackBuffer();
            y++;
            screen.drawCircle(x, y, 2, drawPixel);
        }

        screen.displayScreen();
    }
    

    return 0;
}