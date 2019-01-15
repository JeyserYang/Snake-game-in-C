# Console-Snake-Game-In-C
## 程序主体框架
首先我们确立程序主体框架，对于本例，可分为三个文件，一个是程序运行主体函数main.c，另外两个是游戏头文件snake.h和源文件snake.c，同时程序采取**自顶向下**的设计思想。
- 根据需求，在游戏没有结束时，程序应该一直获取用户输入，然后对用户输入数据进行反应。一开始我们先让贪吃蛇能动起来。因此设计main函数主体为以下内容:
```
int main()
{
    printMap();
    while(!gameOver())
    {
       char ch = getInput();
       switch (ch) {
            case 'W':
                snakeMove(UP);
                break;
            case 'A':
                snakeMove(LEFT);
                break;
            case 'S':
                snakeMove(DOWN);
                break;
            case 'D':
                snakeMove(RIGHT);
                break;
        }
        refresh();
        printMap();
    }
    return 0;
}
```
- 确定程序的数据结构以及初始化，也就是用什么数据来存放整张地图以及贪吃蛇。在这里，我使用的是二维数组。一开始我们可以认为整张地图都是空白，因此map初始化为如下:
```
#define WIDTH           40          //The width of map
#define HEIGHT          20          //The height of map

//WIDTH+1的原因是C中每一个字符串的最后一个字符都是'\0'.
char map[HEIGHT][WIDTH+1];          //The map array

//Initialization the map
void initMap() {
    int i,j;
    for(i=0;i<HEIGHT;i++)
        for(j=0;j<WIDTH;j++)
            map[i][j] = ' ';
}
```
- 在这里，蛇的数据就只是它所在的位置，也就是x，y坐标(设定垂直向下为x轴，水平向右为y轴）。因此设计如下数组，用两个数组分别来存放蛇的x坐标和y坐标，显然，蛇头的坐标永远为currentLength-1。代码如下:
```
#define WINMAXLENGTH    15          //The snake max length while you win

int currentLength = 5;              //The current length of the snake
int snakeX[WINMAXLENGTH] = { 0, 0, 0, 0, 0 };       //The snake x coordinate value
int snakeY[WINMAXLENGTH] = { 0, 1, 2, 3, 4 };       //The snake y coordinate value

//同时在上面的初始化initMap()中添加如下代码
 map[0][0] = map[0][1] =
 map[0][2] = map[0][3] = 'X';    //The snake body: 'X'
 map[0][4] = 'H';                //The snake head: 'H'
```

## 详细设计
- 根据主函数，我们首先需要在屏幕上显示出地图样子，因此printMap函数设计如下:
```
//print the map
void printMap() {
    int i,j;
    for(i=0;i<WIDTH+2;i++)   printf("*");    printf("\n");
    for(i=0;i<HEIGHT;i++) {
        printf("*");
        for(j=0;j<WIDTH;j++)
            putchar(map[i][j]);
        printf("*\n");
    }
    for(i=0;i<WIDTH+2;i++)   printf("*");    printf("\n");
}
```
- 判断程序是否结束，一开始我们可以认为程序永远也不会结束。
```
int gameOver()
{
	return 0;
}
```
- 获取用户输入，这里我们不知道怎样连续获取键盘输入，所以我们首先就用scanf函数。
```
char getInput()
{
	char ch;
	scanf("%c", &ch);
	return ch;
}
```
- 接下来就是让蛇能够移动的函数了。在不考虑撞墙和撞到自己的前提下，由于蛇头和身体的不同，因此应该特别对待，代码如下:
```
#define UP              -1,0
#define DOWN            1,0
#define LEFT            0,-1
#define RIGHT           0,1

//Control the snake's move
void snakeMove(int dx, int dy) {
    int i,j;
    //clear the map
    for(i=0;i<HEIGHT;i++)
        for(j=0;j<WIDTH;j++)
            map[i][j] = ' ';
    //move the snake's body
    for(i=0;i<currentLength-1;i++) {
        snakeX[i] = snakeX[i+1];
        snakeY[i] = snakeY[i+1];
        map[snakeX[i]][snakeY[i]] = 'X';
    }
    //move the snake's head
    snakeX[i] = snakeX[i] + dx;
    snakeY[i] = snakeY[i] + dy;
    map[snakeX[i]][snakeY[i]] = 'H';
}
```
- 增加必要的清空屏幕函数
```
//Clear the window
void refresh() {
    system("cls");
}
```
**Note1**：现在让我们来运行程序，我们应该可以通过一个一个的输入WASD来控制蛇的行走了。

## 不需要每次按下回车键程序才输出结果，实时获取键盘输入。其实很简单，到网上一搜就可以找到，就是使用了两个函数，同时增加了对当前移动方向的判定，也就是说如果用户输入错误或者什么都不输入，蛇也会按照原来的行动方向一直前进。
```
char currentMoveDirection = 'D';    //'W':UP  'S':DOWN  'A':LEFT  'D':RIGHT

//将main函数中switch语句替换为如下代码
if(_kbhit())        snakeMoveDirection(_getch());

//同时添加的snakeMoveDirection函数为如下
void snakeMoveDirection(char direction)
{
	//canEatUpFood():当用户按下W键时，判断蛇是否能吃到上面的食物。
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

//其他类似
void canEatUpFood() {
    if(foodX == (snakeX[currentLength-1]-1) &&
       foodY == snakeY[currentLength-1])
            eatFood();
}

//蛇吃到食物的判定很简单，就是将原来是食物的位置变为蛇头就可以了，蛇的长度加1，再次生成食物
//The snake can eat food
void eatFood() {
    snakeX[currentLength] = foodX;
    snakeY[currentLength] = foodY;
    currentLength++;
    generateFood();
}
```
**Note2**: 至此，贪吃蛇的基本功能就算全部实现了，接下来就是一些细节设计了，包括：难度选择，向左移动时按下向右键不会有反应，上下左右按键也可以控制蛇的移动，判断游戏结束条件，具体代码可参见！[](https://github.com/JeyserYang/Snake-game-in-C/blob/v1.0/src/snake.c)