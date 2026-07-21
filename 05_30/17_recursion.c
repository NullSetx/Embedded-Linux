#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

	/*int count = 0;*/
void test(void)
{
	//局部变量只对当前的函数有效
	//静态的局部变量，是对所有的函数有效，但作用域只对当前的函数
	static int count = 0;

	if (count == 5)
	{
		return ;
	}
	printf("this is my test! count : %d %p\n", count, &count);
	count++;

	test();
}


void test1(int num)
{
	if (num == 0)
		return ;

	printf("test!\n");
	test1(--num);
	/*test1(num - 1);*/
	/*test1(num--);*/


}
int main(void)
{
	/*test();*/
	test1(5);
	return 0;
}
