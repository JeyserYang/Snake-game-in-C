#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH           30
#define HEIGHT          15

#define WINMAXLENGTH    8

#define UP              -1,0
#define DOWN            1,0
#define LEFT            0,-1
#define RIGHT           0,1

char map[HEIGHT][WIDTH+1];

int currentLength = 5;
int snakeX[WINMAXLENGTH] = { 0, 0, 0, 0, 0 };
int snakeY[WINMAXLENGTH] = { 0, 1, 2, 3, 4 };
char currentMoveDirection = 'D';       //'W':UP  'S':DOWN  'A':LEFT  'D':RIGHT

int foodX = 7;
int foodY = 15;

int gameOver = 0;

void generateFood()
{
    srand((unsigned)time(NULL));
    foodX = rand()%HEIGHT;
    foodY = rand()%WIDTH;
}

void initMap()
{
    int i,j;
    for(i=0;i<HEIGHT;i++)
        for(j=0;j<WIDTH;j++)
            map[i][j] = ' ';
    map[0][0] = map[0][1] =
    map[0][2] = map[0][3] = 'X';
    map[0][4] = 'H';
    map[foodX][foodY] = '$';
}

void printMap()
{
    int i,j;
    for(i=0;i<WIDTH+2;i++)   printf("*");    printf("\n");
    for(i=0;i<HEIGHT;i++)
    {
        printf("*");
        for(j=0;j<WIDTH;j++)
            putchar(map[i][j]);
        printf("*\n");
    }
    for(i=0;i<WIDTH+2;i++)   printf("*");    printf("\n");
}

void eatFood()
{
    snakeX[currentLength] = foodX;
    snakeY[currentLength] = foodY;
    currentLength++;
    generateFood();
}

void canEatUpFood()
{
    if(foodX == (snakeX[currentLength-1]-1) &&
       foodY == snakeY[currentLength-1])
            eatFood();
}

void canEatDownFood()
{
    if(foodX == (snakeX[currentLength-1]+1) &&
       foodY == snakeY[currentLength-1])
            eatFood();
}

void canEatLeftFood()
{
    if(foodX == snakeX[currentLength-1] &&
       foodY == (snakeY[currentLength-1]-1))
            eatFood();
}

void canEatRightFood()
{
    if(foodX == snakeX[currentLength-1] &&
       foodY == snakeY[currentLength-1]+1)
            eatFood();
}

void snakeMove(int dx, int dy)
{
    int i,j;
    for(i=0;i<HEIGHT;i++)
        for(j=0;j<WIDTH;j++)
            map[i][j] = ' ';
    for(i=0;i<currentLength-1;i++)
    {
        snakeX[i] = snakeX[i+1];
        snakeY[i] = snakeY[i+1];
        map[snakeX[i]][snakeY[i]] = 'X';
    }
    snakeX[i] = snakeX[i] + dx;
    snakeY[i] = snakeY[i] + dy;
    map[snakeX[i]][snakeY[i]] = 'H';
    map[foodX][foodY] = '$';
}

void snakeMoveDirection(char direction)
{
    if(direction == 'W' && currentMoveDirection != 'S')
    {
        canEatUpFood();
        currentMoveDirection = 'W';
        snakeMove(UP);
    }
    else if(direction == 'S' && currentMoveDirection != 'W')
    {
        canEatDownFood();
        currentMoveDirection = 'S';
        snakeMove(DOWN);
    }
    else if(direction == 'A' && currentMoveDirection != 'D')
    {
        canEatLeftFood();
        currentMoveDirection = 'A';
        snakeMove(LEFT);
    }
    else if(direction == 'D' && currentMoveDirection != 'A')
    {
         canEatRightFood();
         currentMoveDirection = 'D';
         snakeMove(RIGHT);
    }
    else
    {
        snakeMoveDirection(currentMoveDirection);
    }
}

void refresh()
{
    system("cls");
}

int isGameOver()
{
    if(snakeX[currentLength-1] == HEIGHT || snakeX[currentLength-1] == -1 ||
        snakeY[currentLength-1] == WIDTH  || snakeY[currentLength-1] == -1 )
                return 1;
    int i;
    for(i=0;i<currentLength-1;i++)
        if(snakeX[currentLength-1] == snakeX[i] &&
           snakeY[currentLength-1] == snakeY[i])
                return 1;
    return 0;
}

int main()
{
    initMap();
    printMap();
    while(1)
    {
        if(_kbhit())        snakeMoveDirection(_getch());
        else                snakeMoveDirection(currentMoveDirection);
        refresh();
        printMap();
        if(isGameOver())                        break;
        if(currentLength == WINMAXLENGTH)       break;
        Sleep(200);
    }
    if(isGameOver() == 0)
        printf("Congratulation!!! YOU WIN!!!\n");
    else
        printf("HAHAHAHAHAHAHA!!! YOU LOSE!!!\n");
    system("pause");
    return 0;
}
