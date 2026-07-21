#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	//防止编译器优化代码
	volatile int a = 10, b = 20;
	auto signed int c = 30;

	printf("a : %d %p\n", a, &a);
	/*printf("b : %d %p\n", b, &b);*/


	//通过a打印b的数据
	printf("a => b : %d\n", *(&a - 1));
	return 0;
}
