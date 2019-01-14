#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifndef SNAKE_H_INCLUDED
#include "snake.h"
#endif

int main()
{
    printWelcome();
    scanf("%d", &difficulty);
    initMap();
    printMap();
    while(1)
    {
        //get the keyboard input
        if(_kbhit())        snakeMoveDirection(_getch());
        else                snakeMoveDirection(currentMoveDirection);
        refresh();
        printWelcome();
        printMap();
        if(isGameOver())                        break;
        if(currentLength == WINMAXLENGTH)       break;
        sleep();
    }
    if(isGameOver() == 0)
        printf("Congratulation!!! YOU WIN!!!\n");
    else
        printf("HAHAHAHAHAHAHA!!! YOU LOSE!!!\n");
    system("pause");
    return 0;
}
