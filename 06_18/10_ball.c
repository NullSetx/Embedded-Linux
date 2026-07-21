#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ROW 10
#define COL 20

void init(char bg[][COL])
{
	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
			{
				bg[i][j] = '#';
			}
			else
			{
				bg[i][j] = ' ';
			}
		}
	}
}

void show(char bg[][COL])
{
	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			putchar(bg[i][j]);
		}
		putchar(10);
	}

}
int main(void)
{
	char bg[ROW][COL];

	int x = 3, y = 3;
	
	while (1)
	{
		printf("\033[1;1H");
		init(bg);
		bg[x][y] = 'o';
		x++;
		show(bg);
		sleep(1);
	}
	return 0;
}
