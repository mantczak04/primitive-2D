#include <iostream>
#include "Screen.h"



int main()
{
    Screen screen(320, 240); //generates 640x480 because of font size 2px
    screen.setScreenActive();

    while (true) {
        screen.displayScreen();
        for(int i=0; i<320; i+=10)
            for (int j = 10; j < 240; j += 10) {
                screen.drawCircle(i, j, 5, CYAN);
                i++;
            }
                
    }
    

    return 0;
}