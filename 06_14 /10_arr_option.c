#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10

//初始化数组
void arr_init(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
}

void arr_show(int arr[], int size)
{
	int i;

	for (i = 0; i < size; i++)
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

int arr_min(int arr[], int size)
{
	int i;
	int min = arr[0];

	for (i = 1; i < size; i++)
	{
		if (min > arr[i])
		{
			min = arr[i];
		}
	}

	return min;
}

//求最大最小数
//求和 求平均数
int arr_sum(int arr[], int size)
{
	int i;
	int sum = 0;

	for (i = 0; i < size; i++)
	{
		sum += arr[i];	
	}

	return sum;
}

int arr_ave(int arr[], int size)
{
	return arr_sum(arr, size) / size;
}
//排序 升序 降序
void arr_sort(int arr[], int size)
{
	int i, j, tmp;

	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
//查找
int arr_find(int arr[], int size, int key)
{
	int i;

	for (i = 0;  i < size; i++)
	{
		if (key == arr[i])
			return arr[i];
	}

	return -1;
}
//反转
void arr_rever(int arr[], int size)
{
	int i;
	int tmp;

    /*
	 *for (i = size - 1; i >= 0; i--)
	 *{
	 *    
	 *}
     */
	for (i = 0; i < size / 2 ; i++)
	{
		tmp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = tmp;
	}
}
//循环左移 循环右移 指定位数
void arr_left(int arr[], int size, int bit)
{
	int i, tmp, j;

	for (j = 0; j < bit % size; j++)
	{
		tmp = arr[0];
		for (i = 0; i < size - 1; i++)
		{
			arr[i] = arr[i + 1];
		}
		arr[i] = tmp;
	}
}

void arr_right(int arr[], int size, int bit)
{
	arr_left(arr, size, size - (bit % size));
}
int main(void)
{
	int key, ind;
	int arr[MAX];

	srand(time(NULL));

	arr_init(arr, sizeof(arr) / sizeof(arr[0]));
	arr_show(arr, sizeof(arr) / sizeof(arr[0]));

    /*
	 *printf("max : %d\n", arr_max(arr, MAX));
	 *printf("min : %d\n", arr_min(arr, MAX));
	 *printf("sum : %d\n", arr_sum(arr, MAX));
	 *printf("ave : %d\n", arr_ave(arr, MAX));
     */
	/*arr_sort(arr, sizeof(arr) / sizeof(arr[0]));*/
	/*arr_rever(arr, MAX);*/
	printf("input shift left number : ");
	scanf("%d", &key);

	/*arr_left(arr, MAX, key);*/
	arr_right(arr, MAX, key);

	arr_show(arr, sizeof(arr) / sizeof(arr[0]));

    /*
	 *printf("input find number : ");
	 *scanf("%d", &key);
	 *ind = arr_find(arr, sizeof(arr) / sizeof(arr[0]), key);
	 *if (-1 == ind)
	 *{
	 *    printf("no find!\n");
	 *}
	 *else
	 *{
	 *    printf("ind : %d\n", ind);
	 *}
     */
	return 0;
}
