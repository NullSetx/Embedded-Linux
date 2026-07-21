#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int *p = NULL;
	int *q = NULL;

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

	q = p;

	p = (int *)calloc(6, sizeof(int));
	printf("second => p : %p\n", p);

	memcpy(p, q, sizeof(int) * 5);
	free(q);
	q = NULL;
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
