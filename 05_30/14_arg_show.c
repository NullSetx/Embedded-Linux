#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


void test(int num)
{
	printf("num : %d\n", num);
}

int hello(void)
{
	printf("hello!\n");
	return 10;
}

float world(void)
{
	return 3.14;
}
int main(void)
{
	int a = 123;

	test(123);//常量作为函数参数

	test(a);//变量可以作为函数参数

	test(a + 123);//表达式可以作为函数参数

	test(printf("hello!\n"));//函数作为函数参数

	test(hello());

	test(world());
	return 0;
}
