#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//函数调用就是谁调用我，然后返回给谁
void test(void)
{
	if(num == 5)
		return ;
	printf("this is test!\n");
	return ;//表示函数结束，不表示整个程序的退出
	printf("test end!\n");

	test();
}

void test(int num)
{
	if (num == 0)
		return ;
	
	test(num - 1);
}
int main(void)
{
	
	test();
	printf("main end!\n");

	return 0;//整个程序退出
}
