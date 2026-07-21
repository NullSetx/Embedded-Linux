#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


void test(int a)
{
	a = 20;
	printf("test => a = %d\n", a);
}

int main(void)
{
	int a = 10;

	test(a);

	printf("a : %d\n", a);
	return 0;
}
