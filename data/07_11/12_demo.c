#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i, j;
	int **p = NULL;

	//传参  返回
	//test_01(&p, i, j);
	//p = test_02(i, j);

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			p[i][j] = rand() % 100;
		}
	}
	return 0;
}
