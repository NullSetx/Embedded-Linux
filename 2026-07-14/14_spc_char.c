#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

void test(void)
{
	printf("test : line = %d %s %s\n", __LINE__, __func__, __FILE__);//执行
}

int main(void)
{
	
	printf("main => line : %d %s %s\n", __LINE__, __func__, __FILE__);
	test();//调用

	printf("time : %s date : %s\n", __TIME__, __DATE__);

	return 0;
}
