#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


//递归实现过程就是栈实现过程
//先进后出 后进先出
void test(int num)
{
	if (num == 0)
		return ;
	
	test(num - 1);
}

int main(void)
{
	test(5);

	return 0;
}
