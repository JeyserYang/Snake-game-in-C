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
    switch(direction)
    {
        case 'W':       canEatUpFood();     currentMoveDirection = 'W';
                        snakeMove(UP);      break;
        case 'S':       canEatDownFood();   currentMoveDirection = 'S';
                        snakeMove(DOWN);    break;
        case 'A':       canEatLeftFood();   currentMoveDirection = 'A';
                        snakeMove(LEFT);    break;
        case 'D':       canEatRightFood();  currentMoveDirection = 'D';
                        snakeMove(RIGHT);   break;
        default:        snakeMoveDirection(currentMoveDirection);
    }
}

void refresh()
{
    Sleep(200);
    system("cls");
}

int main()
{
    initMap();
    printMap();
    while(!gameOver)
    {
        if(_kbhit())        snakeMoveDirection(_getch());
        else                snakeMoveDirection(currentMoveDirection);
        if(currentLength == WINMAXLENGTH)
            break;
        refresh();
        printMap();
    }
    printf("Congratulation!!! YOU WIN!!!\n");
    system("pause");
    return 0;
}
