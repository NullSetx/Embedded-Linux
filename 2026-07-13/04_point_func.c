#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int *test(void)
{
	static int a = 10;//非静态局部变量

	{
		int a;
	}
	return &a;
}

void test01(void)
{
	int b = 20;
}

int main(void)
{
	int *p = NULL;

	p = test();
	
	test01();
	printf("*p : %d\n", *p);
	return 0;
}
