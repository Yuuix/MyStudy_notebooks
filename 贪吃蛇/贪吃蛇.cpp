#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>    //图形库
#include<conio.h>       //按键交互 _getch()
#include<time.h>        //随机函数srand()
#include<stdlib.h>      //控制蛇的速度Sleep()
#define pixl 10
#define speed 100
//数据设计

//方向
enum Direction {up, down, left, right};    //方向只包含四个（上下左右）

//坐标
struct Coordinate
{
	int x;
	int y;
};

//蛇的属性
struct Snake
{
	Snake()
	{
		this->length = 3;
		for (int i = 0; i < this->length; ++i)
		{
			this->s_point[i].x = (3 - i - 1) * pixl;
			this->s_point[i].y = 0;
		}
		this->dir = right;
	}

	Coordinate s_point[100];        //蛇的长度最大为100节
	int length;                     //长度
	Direction dir;                  //方向
};

//食物
struct Food
{
	Coordinate f_point;
	bool IsExistence = false;
	int score=0;
};

//窗口句柄
HWND hwnd = NULL;


//void init_snake()    //初始化蛇
//{
//	Snake snake;
//}

//显示🐍
void print_snake(Snake& snake)
{
	for (int i = 0; i < snake.length; ++i)
	{
		setlinecolor(BLACK);
		setfillcolor(GREEN);
		fillrectangle(snake.s_point[i].x,snake.s_point[i].y,snake.s_point[i].x+pixl, snake.s_point[i].y+pixl);
	}
}

//🐍的移动
void move_snake(Snake& snake)
{
	for (int i = snake.length - 1; i > 0; --i)
	{
		snake.s_point[i].x = snake.s_point[i - 1].x;
		snake.s_point[i].y = snake.s_point[i - 1].y;
	}

	switch (snake.dir)
	{
	case up:
		snake.s_point[0].y -= pixl;
		break;
	case down:
		snake.s_point[0].y += pixl;
		break;
	case left:
		snake.s_point[0].x -= pixl;
		break;
	case right:
		snake.s_point[0].x += pixl;
		break;
	default:
		break;
	}
}

//键位控制
void keyCtrl(Snake& snake)
{
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':
		if (snake.dir == down)
		{
			break;
		}
		else
		{
			snake.dir = up;
		}
		break;
	case 's':
	case 'S':
		if (snake.dir == up)
		{
			break;
		}
		else
		{
			snake.dir = down;
		}
		break;
	case 'a':
	case 'A':
		if (snake.dir == right)
		{
			break;
		}
		else
		{
			snake.dir = left;
		}
		break;
	case 'd':
	case 'D':
		if (snake.dir == left)
		{
			break;
		}
		else
		{
			snake.dir = right;
		}
		break;

	}
}

void init_food(Food& food,Snake& snake)
{
	if (!food.IsExistence)
	{
		srand((unsigned int)time(NULL));
		food.f_point.x = rand() % 80 * pixl;
		food.f_point.y = rand() % 60 * pixl;
		food.IsExistence = true;

		for (int i = 0; i < snake.length; i++)
		{
			if (food.f_point.x == snake.s_point[i].x && food.f_point.y == snake.s_point[i].y)
			{
				food.f_point.x = rand() % 80 * pixl;
				food.f_point.y = rand() % 60 * pixl;
			}
		}
	}
}

void print_food(Food& food)
{
	setfillcolor(RED);
	fillrectangle(food.f_point.x, food.f_point.y, food.f_point.x + pixl, food.f_point.y + pixl);

}

void eatfood(Snake& snake,Food& food)
{
	if (snake.s_point[0].x == food.f_point.x && snake.s_point[0].y == food.f_point.y)
	{
		food.IsExistence = false;
		snake.length++;
		food.score += 10;
	}
}

void showscore(Food& food)
{
	char grade[100] = "";
	sprintf(grade,"分数：%d", food.score);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(650, 30, grade);
}

int endgame(Snake& snake)
{
	if (snake.s_point[0].x < 0 || snake.s_point[0].x>800 || snake.s_point[0].y < 0 || snake.s_point[0].y>600)
	{
		MessageBox(hwnd, "碰撞墙壁", "GAME OVER!", 0);
		return 1;
	}
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.s_point[0].x == snake.s_point[i].x && snake.s_point[0].y == snake.s_point[i].y)
		{
			MessageBox(hwnd, "你自杀了", "GAME OVER!", 0);
			return 1;
		}
	}
	return 0;
}

int main()
{	
	//绘制窗口
	hwnd=initgraph(800, 600); //窗口大小为800*600
	setbkcolor(YELLOW); //设置为白色
	cleardevice();    //刷新

	Snake snake;
	Food food;
	while (1)
	{
		cleardevice();
		init_food(food, snake);
		print_food(food);
		eatfood(snake, food);
		showscore(food);
		print_snake(snake);
		move_snake(snake);
		if (endgame(snake))
		{
			break;
		}
		if (_kbhit())
		{
			keyCtrl(snake);
		}

		Sleep(speed);
	}

	closegraph();


	return 0;
}