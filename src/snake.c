#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH           30          //The width of map
#define HEIGHT          15          //The height of map

#define WINMAXLENGTH    15          //The snake max length while you win

#define UP              -1,0
#define DOWN            1,0
#define LEFT            0,-1
#define RIGHT           0,1

char map[HEIGHT][WIDTH+1];          //The map array

int currentLength = 5;              //The current length of the snake
int snakeX[WINMAXLENGTH] = { 0, 0, 0, 0, 0 };       //The snake x coordinate value
int snakeY[WINMAXLENGTH] = { 0, 1, 2, 3, 4 };       //The snake y coordinate value
char currentMoveDirection = 'D';    //'W':UP  'S':DOWN  'A':LEFT  'D':RIGHT

int foodX = 7;                      //The food x coordinate value
int foodY = 15;                     //The food y coordinate value

int gameOver = 0;                   //The condition of game over.

//Generate food random position.
void generateFood()
{
    srand((unsigned)time(NULL));
    foodX = rand()%HEIGHT;
    foodY = rand()%WIDTH;
}

//Initialization the map
void initMap()
{
    int i,j;
    for(i=0;i<HEIGHT;i++)
        for(j=0;j<WIDTH;j++)
            map[i][j] = ' ';
    map[0][0] = map[0][1] =
    map[0][2] = map[0][3] = 'X';    //The snake body: 'X'
    map[0][4] = 'H';                //The snake head: 'H'
    map[foodX][foodY] = '$';        //The food: '$'
}

//print the map
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

//The snake can eat food
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

//Control the snake's move
void snakeMove(int dx, int dy)
{
    int i,j;
    //clear the map
    for(i=0;i<HEIGHT;i++)
        for(j=0;j<WIDTH;j++)
            map[i][j] = ' ';
    //move the snake's body
    for(i=0;i<currentLength-1;i++)
    {
        snakeX[i] = snakeX[i+1];
        snakeY[i] = snakeY[i+1];
        map[snakeX[i]][snakeY[i]] = 'X';
    }
    //move the snake's head
    snakeX[i] = snakeX[i] + dx;
    snakeY[i] = snakeY[i] + dy;
    map[snakeX[i]][snakeY[i]] = 'H';
    map[foodX][foodY] = '$';
}

//Judge the snake move path by the player's control
void snakeMoveDirection(char direction)
{
    //the player press the 'W' or 'UP' while snake's move direction is not opposite
    if((direction == 'W' || direction == 72) && currentMoveDirection != 'S')
    {
        canEatUpFood();
        currentMoveDirection = 'W';
        snakeMove(UP);
    }
    else if((direction == 'S' || direction == 80) && currentMoveDirection != 'W')
    {
        canEatDownFood();
        currentMoveDirection = 'S';
        snakeMove(DOWN);
    }
    else if((direction == 'A' || direction == 75) && currentMoveDirection != 'D')
    {
        canEatLeftFood();
        currentMoveDirection = 'A';
        snakeMove(LEFT);
    }
    else if((direction == 'D' || direction == 77) && currentMoveDirection != 'A')
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

//Clear the window
void refresh()
{
    system("cls");
}

//Judge whether the game is over
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
        //get the keyboard input
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
