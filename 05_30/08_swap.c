#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void swap(int a, int b)
{
	int tmp;

	printf("swap : a = %d %p b = %d %p\n", a, &a, b, &b);

	tmp = a;
	a = b;
	b = tmp;
	printf("swap : a = %d b = %d\n", a, b);



}

int main(void)
{
	int a = 10, b = 20;
	int tmp;

	printf("before : a = %d %p b = %d %p\n", a, &a, b, &b);
	swap(a, b);
	printf("after  : a = %d b = %d\n", a, b);
	

	return 0;
}
