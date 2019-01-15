#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define WIDTH           40          //The width of map
#define HEIGHT          20          //The height of map

#define WINMAXLENGTH    15          //The snake max length while you win

#define UP              -1,0
#define DOWN            1,0
#define LEFT            0,-1
#define RIGHT           0,1

extern int currentLength;
extern char currentMoveDirection;
extern int difficulty;

void printWelcome();
void initMap();
void printMap();
void snakeMoveDirection(char direction);
void refresh();
void sleep();
int isGameOver();

#endif // SNAKE_H_INCLUDED
