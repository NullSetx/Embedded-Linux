#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define MAX 2000000
/*#define MAX 10*/

void init(int *arr)
{
	int i;

	for (i = 0 ; i < MAX; i++)
	{
		arr[i] = rand() % MAX;
	}
}

void show(int *arr)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar(10);
}

//交换排序：取出一个数据跟后面所有的数据比较，满足条件则交换
void swap(int *arr)
{
	int i, j;
	int tmp;

	for (i = 0; i < MAX; i++)
	{
		for (j = i + 1; j < MAX; j++)
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

//冒泡排序：相邻的两个数比较，小数上浮，大数沉低
void bubble(int *arr)
{
	int i, j;

	for (i = 0; i < MAX; i++)
	{
		/*printf("%d : ", i);*/
		for (j = 0; j < MAX - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				arr[j] ^= arr[j + 1];
				arr[j + 1] ^= arr[j];
				arr[j] ^= arr[j + 1];
			}
		}
        /*
		 *show(arr);
		 *getchar();
         */
	}
}
//
//选择排序
//取出一个数根后面所有的数据比较，
//满足条件，则保存最小值的小标
//
void my_select(int *arr)
{
	int i, j, min;
	int tmp;
	for (i = 0; i < MAX; i++)
	{
		min = i;
		for (j = i + 1; j < MAX; j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
			
		}
	}
}
//插入排序
//取出第二个数据，跟前面的数据比较，如果满足条件，则把前一个给后一个
//如果不满足条件，则退出循环，并保存比较数据给当前的位置，依次类推。
//
//升序 有小到大
void insert(int *arr)
{
	int i, j, save;

	for (i = 1; i < MAX; i++)
	{
		save = arr[i];
		for (j = i; j > 0; j--)
		{
			if (save < arr[j - 1])
			{
				arr[j] = arr[j - 1];
			}
			else
			{
				break;
			}
		}
		arr[j] = save;
	}
}
int count = 0;

void stack_size(void)
{
	//大约12M
	char buf[1024];
	printf("count : %d\n", count++);
	stack_size();
}

int cmp(const void *d1, const void *d2)
{
	return *((int *)d1) - *((int *)d2);
}

void my_qsort(int *arr, int l, int h)
{
	int base = arr[l];
	int low = l;
	int high = h;

	if (l > h)
		return ;

	while (l < h)
	{
        /*
		 *printf("l : %d h : %d\n", l, h);
		 *getchar();
         */
		while (base < arr[h] && l < h)
			h--;
		if (l < h)
		{
			arr[l] = arr[h];
			l++;
		}

		while(base > arr[l] && l < h)
			l++;
		if (l < h)
		{
			arr[h] = arr[l];
			h--;
		}
	}
	/*printf("l : %d, h : %d\n", l, h);*/
	arr[l] = base;

	my_qsort(arr, low, l - 1);
	my_qsort(arr, l + 1, high);
}

int main(int argc, char *argv[])
{

	/*stack_size();*/
	int arr[MAX];//局部变量 => stack

	/*srand(time(NULL));*/
	init(arr);
    /*
	 *show(arr);
	 *my_qsort(arr, 0, MAX - 1);
	 *show(arr);
     */
	switch (atoi(argv[1]))
	{
		case 1:
			printf("swap : \n");
			swap(arr);
			break;
		case 2:
			printf("bubble : \n");
			bubble(arr);
			break;
		case 3:
			printf("select : \n");
			my_select(arr);
			break;
		case 4:
			printf("insert : \n");
			insert(arr);
			break;
		case 5:
			printf("qsort : \n");
			qsort(arr, MAX, sizeof(int), cmp);
			break;
		case 6:
			printf("qsort : \n");
			my_qsort(arr, 0, MAX - 1);
			break;
	}

	return 0;
}


