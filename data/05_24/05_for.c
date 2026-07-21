#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	//定义循环变量
	int i;

	for (i = 1/*init*/; i < 10/*con*/; i++/*add*/)
	{
		printf("%d ", i);//body
	}
	putchar(10);
	printf("i : %d\n", i);
	//1 2 3 4 5 6 7 8 9
	//init 只会执行一次
	////init => con => body => add => con => body => add => ...
	//	=> con ?
	//
	
	for (i = 9; i > 0; i--)
	{
		printf("%d ", i);
	}
	putchar(10);

	/*for (i = 9; i > 0; i--, i--)*/
	for (i = 9; i > 0; i -= 2)
	{
		printf("%d ", i);
	}
	putchar(10);


	return 0;
}
