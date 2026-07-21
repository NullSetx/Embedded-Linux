#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int *test(void)
{
	static int a = 123;

	return &a;
}

void test_01(void)
{
	int b = 456;
}

int main(void)
{
	int *p = NULL;

	p = test();
	
	test_01();

	printf("*p : %d\n", *p);
	return 0;
}
