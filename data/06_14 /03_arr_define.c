#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	//定义整形的数组并初始化
	int arr[5] = {1,2,3,4,5};

	//访问：是通过数组的小标来访问
	//且第一个数据成员的小标是从0开始
	printf("arr[0] : %d\n", arr[0]);
	arr[1] = 123;
	printf("arr[1] : %d\n", arr[1]);

	printf("==================\n");
	//循环访问
	
	for (i = 0; i < 5; i++)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
	}
	return 0;
}
