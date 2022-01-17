#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

#define SNAKE_NUM 500
#define MAX_WEIGHT 40
#define MAX_HEIGHT 20

enum DIR
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

struct Pos
{
    int x;
    int y;
};

struct Snake
{
    int size;
    int dir;
    int speed;
    struct Pos pos[SNAKE_NUM];
}snake;

struct Food
{
    struct Pos pos;
    int isEat;
}food;

void makeFood()
{
    srand((unsigned)time(NULL));
    food.pos.x = rand() % MAX_WEIGHT;
    srand((unsigned)time(NULL));
    food.pos.y = rand() % MAX_HEIGHT;
    food.isEat = 1;
}

void isFood()
{
    if(food.isEat == 0)
    {
        makeFood();
    }
    else
    {
        return;
    }
}

void gameInit()
{
    snake.size = 3;
    snake.dir = RIGHT;
    snake.speed = 1;
    snake.pos[0].x = 1;
    snake.pos[0].y = 1;
    food.isEat = 0;
    for(int i = 0; i < snake.size; i++){
        snake.pos[i].x = i;
        snake.pos[i].y = 1;
    }
}

void gameDraw()
{
    system("cls");
    for(int i = 0; i < MAX_HEIGHT; i++)
    {
        for(int j = 0; j < MAX_WEIGHT; j++)
        {
            int count = 0;
            for(int x = 0; x < snake.size; x++)
            {
                if(i == snake.pos[x].y &&
                   j == snake.pos[x].x)
                {
                    count++;
                }
            }
            if(count == 0)
            {
                if(food.isEat == 1 && 
                   food.pos.x == j &&
                   food.pos.y == i)
                {
                    printf("@");
                }
                else
                {
                    printf(" ");
                }
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

void snakeMove()
{
    if(snake.pos[0].x == food.pos.x &&
       snake.pos[0].y == food.pos.y)
    {
        snake.size++;
        food.isEat = 0;
    }
    for(int i = snake.size-1; i > 0; i--)
    {
        snake.pos[i] = snake.pos[i-1];
    }
    switch (snake.dir)
    {
    case UP:
        if(snake.pos[0].y > 0)
        {
            snake.pos[0].y--;
        }   
        else
        {
            snake.pos[0].y = MAX_HEIGHT - 1;
        }
        break;
    case DOWN:
        if(snake.pos[0].y < MAX_HEIGHT)
        {
            snake.pos[0].y++;
        }   
        else
        {
            snake.pos[0].y = 0;
        }
        break;
    case LEFT:
        if(snake.pos[0].x > 0)
        {
            snake.pos[0].x--;
        }   
        else
        {
            snake.pos[0].x = MAX_WEIGHT - 1;
        }
        break;
    case RIGHT:
        if(snake.pos[0].x < MAX_WEIGHT)
        {
            snake.pos[0].x++;
        }   
        else
        {
            snake.pos[0].x = 0;
        }
        break;
    default:
        break;
    }
}

void keyControl()
{
    if(!_kbhit())
    {
        return;
    }
    switch (_getch())
    {
    case 'W':
    case 'w':
    case 72:
        snake.dir = UP;
        break;
    case 'A':
    case 'a':
    case 80:
        snake.dir = LEFT;
        break;
    case 'S':
    case 's':
    case 75:
        snake.dir = DOWN;
        break;
    case 'D':
    case 'd':
    case 77:
        snake.dir = RIGHT;
        break;
    default:
        break;
    }
}

int main(int agrc, char* argv[])
{
    gameInit();
    gameDraw();
    while (1)
    {   
        isFood();
        keyControl();
        snakeMove();
        gameDraw();
        Sleep(20);
    }
    return 0;
}
