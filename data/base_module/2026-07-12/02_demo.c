#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 8

int **init(int row, int col)
{
	int i;
	int **p = NULL;

	p = (int **)malloc(sizeof(int *) * row);
	if (NULL == p)
	{
		return NULL;
	}

	for (i = 0; i < row; i++)
	{
		p[i] = (int *)malloc(sizeof(int) * col);
		if (p[i] == NULL)
		{
			while (i--)
			{
				free(p[i]);
			}
			free(p);
			return NULL;
		}
	}
	return p;
}

int main(void)
{
	int **p = NULL;
	int i, j;

	p = init(ROW, COL);
	if (p == NULL)
	{
		return -1;
	}
	//传参 返回
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			p[i][j] = rand() % 100;
		}
	}
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			printf("%d ", p[i][j]);
		}
		putchar(10);
	}

	i = ROW;
	while (i--)
	{
		free(p[i]);
	}
	free(p);
	return 0;
}
