#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static int count = 0;

void *my_malloc(int size)
{

	count++;
	return malloc(size);
}

void my_free(void *p)
{
	count--;
	free(p);
}
int counter(void)
{
	return count;
}


int main(void)
{
	int *p = NULL;
	int *q = NULL;

	p = (int *)my_malloc(sizeof(int));
	
	q = (int *)my_malloc(100);

	my_free(p);
	my_free(q);
	printf("count : %d\n", counter());
	return 0;
}
