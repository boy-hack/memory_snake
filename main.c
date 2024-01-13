#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 16
#define HEIGHT 20
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int gameover;
int tailX[100], tailY[100];
int fruitX, fruitY;
int headX, headY;
int dir;
char* map;

void Setup()
{
    gameover = 0;
    dir = 0; // 初始方向为停止
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void setmap(int height,int width,char x){
    // height i
    // width j
    map[height * WIDTH + width] = x;
    
}
void Draw()
{
    for (int i = 0; i < WIDTH; i++)
        setmap(0,i,'#');

    for (int i = 1; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                setmap(i,j,'#');
            else if (j == WIDTH - 1)
                setmap(i,j,'#');
            else if (i == headY && j == headX)
                setmap(i,j,'O');
            else if (i == fruitY && j == fruitX)
                setmap(i,j,'F');
            else
            {
                int printTail = 0;
                for (int k = 0; k < length; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        setmap(i,j,'o');
                        printTail = 1;
                    }
                }

                if (!printTail)
                    setmap(i,j,' ');
            }
        }
    }

    for (int i = 0; i < WIDTH; i++)
        setmap(HEIGHT,i,'#');
}

void AutoPlay()
{
    // 使用简单的算法，使贪吃蛇朝着水果的方向移动
    if (fruitX < headX)
        dir = LEFT;
    else if (fruitX > headX)
        dir = RIGHT;
    else if (fruitY < headY)
        dir = UP;
    else if (fruitY > headY)
        dir = DOWN;
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < length; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    }

    if (headX < 1 || headX >= WIDTH - 1 || headY < 1 || headY >= HEIGHT - 1)
        gameover = 1;
        
    if (length > 100){
        gameover = 1;

    }
    for (int i = 0; i < length; i++)
    {
        if (tailX[i] == headX && tailY[i] == headY)
            gameover = 1;
    }

    if (headX == fruitX && headY == fruitY)
    {
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        length++;
    }
}

int main()
{
    map = malloc(WIDTH * HEIGHT);
    printf("memory address: %p\n",map);
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        map[i] = ' ';
    while (1){
        Setup();

        while (!gameover)
        {
            Draw();
            AutoPlay();
            Logic();
            Sleep(70); // 控制游戏速度
        }
    }

    return 0;
}