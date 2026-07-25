#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//函数名表示函数的地址
void test(void)
{
	printf("this is test!\n");
}

void hello(void)
{
	printf("this is hello!\n");
}

int add(int a, int b)
{
	/*printf("this is add!\n");*/
	return a + b;
}
int sub(int a, int b)
{
	/*printf("this is add!\n");*/
	return a - b;
}

void print(int a, int b, int (*func)(int, int))
{
	printf("result : %d\n", func(a, b));
}
int main(void)
{
	//定义函数指针的变量
	void (*p)(void) = NULL;//只能指向函数返回类型是void 且无参函数类型
	int (*q)(int, int) = NULL;

	p = test;
	p = hello;
	p();
	q = add;
	printf("ret : %d\n", q(2, 3));

	print(3, 2, add);
	print(3, 2, sub);

	return 0;
}
