#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test(int a)//临时变量
{
	printf("test : a = %d\n", a);
}

int main(void)
{
	int a = 10;//在整个main函数内有效
	int b; //局部变量 => stack => 由高到底
	

	test(a);
	printf("test : %p\n", test);

	{
	int a = 20;//只在{}模块内有效
	{
		int a = 30;
	}
	printf("mode : a = %d\n", a);
	}
	printf("&a : %p a : %d\n", &a, a);//就近原则
	printf("&b : %p\n", &b);
	return 0;
}
