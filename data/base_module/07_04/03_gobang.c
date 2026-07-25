#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ROW 10
#define COL 10

void show(int bg[][COL])
{
	int i, j;

	printf("  ");
	for (i = 0; i < COL; i++)
	{
		printf("%d ", i);
	}
	putchar(10);

	for (i = 0; i < ROW; i++)
	{
		printf("%d ", i);
		for (j = 0; j < COL; j++)
		{
			if (bg[i][j] == 0)
			{
				printf("+ ");
			}
			else if (bg[i][j] == 1)
			{
				printf("A ");
			}
			else if (bg[i][j] == -1)
			{
				printf("B ");
			}
		}
		putchar(10);
	}
}
//判断棋子是否有效
int check(int bg[][COL], int x, int y)
{
	//1判断是否越界
	if (x < 0 || x > ROW - 1)
		return -1;

	if ( y < 0 || y > COL - 1)
		return -2;

	//2 不可以吃子 1 -1
	if (bg[x][y] != 0)
		return -3;

	return 0;	
}


int game_over(int bg[][COL], int x, int y, int flag)
{
	int i, count = 0;
	//------------
	for (i = y - 4; i <= y + 4; i++)
	{
		if (i < 0 || i > COL - 1)
		{
			continue;
		}
		else if (bg[x][i] == flag)
		{
			count++;
			if (count == 5)
			{
				return 1;
			}
		}
		else
		{
			count = 0;
		}
	}

	return 0;
	
}


int main(void)
{
	int bg[ROW][COL] = {};
	int flag = 1;//1 表示白棋(A)  -1 表示黑棋(B)
	int x, y;


	while (1)
	{
		/*printf("\033[1;1H");*/
		system("clear");
		show(bg);
		printf("[ %s ] 下子: \033[K", flag == 1 ? "白棋": "黑棋");
		scanf("%d%d", &x, &y);

		//非零表示无效棋子 0 表示有效
		if (check(bg, x, y))
		{
			continue;
		}

		bg[x][y] = flag;

		//判断输赢 1 表示获得胜利 0 表示继续 
		if (game_over(bg, x, y, flag))
		{
			printf("[ %s ] 获取胜利^_^\n", flag == 1 ? "白棋": "黑棋");
			break;
		}
		flag = -flag;
	}

	//  |
	//  /
	//  \
	
	return 0;
}
