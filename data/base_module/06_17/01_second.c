#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

void init(int arr[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		arr[i] = rand() % 8;
	}
}

void show(int arr[], int size)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	putchar(10);	
}

int arr_second(int arr[], int size)
{
	int max, second;
	int i, j, count = 0;;


	max = second = -1;

	for (i = 0; i < size; i++)
	{
		for (j = 0, count = 0; j < size; j++)
		{
			if (arr[i] == arr[j])
			{
				count++;
			}
		}
		if (count == 1)
		{
			//表示不重复的数据
			printf("%d ", arr[i]);

			if (max < arr[i])
			{
				second = max;
				max = arr[i];
			}
			else if (second < arr[i])
			{
				second = arr[i];
			}
		}

	}
	putchar(10);

	return second;
}

int main(void)
{
	int arr[10];
	int ret;

	srand(time(NULL));

	init(arr, MAX);

	show(arr, MAX);

	ret = arr_second(arr,MAX);
	if (ret == -1)
	{
		printf("no second!\n");
	}
	else
	{
		printf("second : %d\n", ret);
	}
	return 0;
}
