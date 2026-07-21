#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	//定义
	int arr[10];
	int sum = 0;

	//初始化
	for (i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}

	//遍历
	for (i = 0; i < 10; i++)
	{
		printf("arr[%d] : %d\n", i, arr[i]);
	}
	//累加
	for (i = 0; i < 10; i++)
	{
		sum += arr[i];
	}
	printf("sum : %d\n", sum);
	return 0;
}
