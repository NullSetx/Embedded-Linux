#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

//初始化数组
void arr_init(int arr[], int size)
{
	int i;
	printf("init => &arr : %p arr : %p\n", &arr, arr);
	printf("init => len : %d\n", sizeof(arr) / sizeof(arr[0]));
	printf("inti => sizeof(arr) : %d\n", sizeof(arr));
	printf("inti => sizeof(arr[0]) : %d\n", sizeof(arr[0]));
	for (i = 0; i < size; i++)
	/*for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)*/
	/*for (i = 0; i < 10; i++)*/
	{
		arr[i] = rand() % 100;
	}
}

void arr_show(int arr[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	/*for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)*/
	/*for (i = 0; i < 10; i++)*/
		printf("%d ", arr[i]);

	putchar(10);	
}

//求最大数
int arr_max(int arr[], int size)
{
	int i;
	int max = arr[0];

	for (i = 1; i < size; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
		}
	}

	return max;
}


//求最大最小数
//求和 求平均数
//排序 升序 降序
//查找
//反转
//循环左移 循环右移 指定位数

int main(void)
{
	int arr[MAX];

	srand(time(NULL));

	printf("len : %d\n", sizeof(arr) / sizeof(arr[0]));
	printf("main  => sizeof(arr) : %d\n", sizeof(arr));
	printf("main  => sizeof(arr[0]) : %d\n", sizeof(arr[0]));
	printf("main => &arr : %p arr : %p\n", &arr, arr);
	printf("================\n");
	arr_init(arr, sizeof(arr) / sizeof(arr[0]));

	arr_show(arr, sizeof(arr) / sizeof(arr[0]));


	printf("max : %d\n", arr_max(arr, MAX));
	return 0;
}
