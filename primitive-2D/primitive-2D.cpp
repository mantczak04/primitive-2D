#include <iostream>
#include "Screen.h"
#include "Player.h"
#include "Sprite.h"

int main()
{
    Screen screen(320, 240); //generates 640x480 because of font size 2px
    screen.setScreenActive();

    int x = 160;
    int y = 120;
    Pixel drawPixel = Pixel{ MAGENTA, NORMAL };
    Sprite man("G:/C++/primitive-2D/primitive-2D/sprites/main.png");
    Sprite coin("G:/C++/primitive-2D/primitive-2D/sprites/coin.png");

    //man.drawSprite(5,5,screen);
    //coin.drawSprite(30, 30, screen);
    WORD colors[] = { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE };

    int xStart = 1;
    int yStart = 1;

    for (WORD color : colors) {
        screen.drawRectangle(xStart, yStart, 16, 16, { color, NORMAL });
        screen.drawRectangle(xStart, yStart+16, 16, 16, { color, DARK });
        xStart += 16;
    }


    while (true) {

        


        if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
        {
           //screen.clearBackBuffer();
           y--;
           screen.drawCircle(x, y, 5, drawPixel);
           
        }

        screen.displayScreen();
    }
    

    return 0;
}