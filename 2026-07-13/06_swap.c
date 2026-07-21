#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(void)
{
	int a = 10, b = 20;
	void *p = NULL;
	//定义函数指针
	/*(void)(*p)(int *, int *);*/
	
	p = swap;


	((void (*)(int *, int *))p)(&a, &b);

	printf("a : %d b : %d\n", a, b);
	return 0;
}
