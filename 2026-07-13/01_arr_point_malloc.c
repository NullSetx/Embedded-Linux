#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#define ROW 2
#define COL 3

//多维数组跟数组指针是等价
int main(void)
{
	int i, j;
	int (*p)[COL] = NULL;//数组指针

	p = (int (*)[COL])malloc(sizeof(int [COL]) * ROW);
	if (NULL == p)
	{
		return -1;
	}

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			p[i][j] = rand() % 100;
		}
	}

	free(p);
	p = NULL;
	return 0;
}
