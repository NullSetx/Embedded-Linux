#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int *p = NULL;

	/*p = (int *)calloc(5, sizeof(int));*/
	p = (int *)malloc(sizeof(int) * 5);
	if (p == NULL)
	{
		return -1;
	}
	printf("first => p : %p\n", p);

	for (i = 0; i < 5; i++)
	{
		p[i] = rand() % 100;
	}


	for (i = 0; i < 5; i++)
	{
		printf("%d ", p[i]);
	}
	putchar(10);


	//表示在原有空间的基础上申请内存空间
	p = (int *)realloc(p, sizeof(int) * 6);
	
	printf("second => p : %p\n", p);

	p[5] = 123;
	for (i = 0; i < 6; i++)
	{
		printf("%d ", p[i]);
	}
	putchar(10);

	free(p);
	p = NULL;

	return 0;
}
