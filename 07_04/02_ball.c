#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ROW 15
#define COL 40

void init(char bg[][COL], char ch)
{
	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
			{
				bg[i][j] = ch;
			}
			else
			{
				bg[i][j] = ' ';
			}
		}
	}
}

void show(char bg[][COL], int color)
{
	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (bg[i][j] == 'o')
			{
				printf("\033[%dmo\033[0m", color);
			}
			else
				putchar(bg[i][j]);
		}
		putchar(10);
	}
}

int main(void)
{
	char bg[ROW][COL] = {};
	int x, y, x_inc = 1, y_inc = 1, color = 31;

	x = y = 3;
	while (1)
	{
		printf("\033[1;1H");
		init(bg, '#');
		bg[x][y] = 'o';
		if (x > ROW - 2 || x < 1)
		{
			x_inc = -x_inc;
			color = rand() % 7 + 31;
		}
		if (y > COL - 2 || y < 1)
		{
			y_inc = -y_inc;
			color = rand() % 7 + 31;
		}
		x += x_inc;
		y += y_inc;

		show(bg, color);
		usleep(200000);
	}

	return 0;
}
