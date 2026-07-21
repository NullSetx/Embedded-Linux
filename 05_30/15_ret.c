#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int test(void)
{
	int a = 1122;
	
	return  printf("hello!\n");

	return a + 2;

	return a;//变量
	
	return 10;//常量可以作为函数返回值

}

int main(void)
{
	printf("ret : %d\n", test());
	return 0;
}
