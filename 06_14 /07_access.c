#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10


int main(void)
{
	int arr[MAX] = {};
	int a = 123;

	//访问范围：0 ~ MAX - 1
	//
	printf("arr[MAX - 1] : %d\n", arr[MAX - 1]);
	//数组并不可以越界访问，导致数据不安全或者段错误
	printf("arr[MAX] : %d\n", arr[MAX]);

	//不允许上下越界访问
	arr[-1] = 345;
	printf("arr[-1] : %d\n", arr[-1]);
	return 0;
}
