#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define I 2
#define J 3
#define K 2

void init(int arr[][J][K])
{
	int i, j, k;
	for (i = 0; i < I; i++)
	{
		for (j = 0; j < J; j++)
		{
			for (k = 0; k < K; k++)
			{
				arr[i][j][k] = rand() % 100;
			}
		}
	}


}

void show(int arr[][J][K])
{
	int i, j, k;
	for (i = 0; i < I; i++)
	{
		for (j = 0; j < J; j++)
		{
			for (k = 0; k < K; k++)
			{
				printf("%d ", arr[i][j][k]);
			}
			printf("\n");
		}
		putchar(10);
		putchar(10);
	}


}
int main(void)
{
	#if 0
	int arr[I][J][K];

	init(arr);

	show(arr);

	printf("=================\n");

	//&arr => sizeof(type) * 所有下标的数据 4 * 2 * 3 * 2 => 48
	printf("&arr : %p & arr + 1 : %p\n", &arr, &arr + 1);
	//arr  => sizeof(type) * 去除第一个小标剩余所有小标乘积大小 4 * 3 * 2 => 24
	//arr[0] => sizeof(type) * 去除前面两个小标剩余所有小标乘积大小
	//arr[0][0] => 4
	//
	//
	//&arr[0][0][0] => 4
	
	#endif
	int arr[2][4][3][2][5][2][3];
	//sizeof(arr) => 2 * 4 * 3 * 2 * 5 * 2 * 3 * sizeof(type)
	//sizeof(a[0]) => 
	//arr[0][0][0] => 偏移大小
	printf("arr[0][o][0] : %p arr[0][0][0] + 1 : %p\n", 
		arr[0][0][0], arr[0][0][0] + 1);
	return 0;
}
