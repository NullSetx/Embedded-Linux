#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define MAX 10


int cmp(const void *d1, const void *d2)
{
	return *((int *)d1) - *((int *)d2);
}
void init(int *arr)
{
	int i;

	for (i = 0 ; i < MAX; i++)
	{
		arr[i] = rand() % 100;
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
		printf("%d ", i);
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
		show(arr);
		getchar();
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
		printf("%d : ", i);
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
		show(arr);
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

int find(int *arr, int key)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		if (arr[i] == key)
			return arr[i];
	}

	return -1;
}

int my_bsearch(int *arr, int l, int h, int key)
{
	int m = (l + h) / 2;

	while (l <= h)
	{
		m = (l + h) / 2;
		if (key > arr[m])
		{
			l = m + 1;
		}
		else if (key < arr[m])
		{
			h = m - 1;
		}
		else
		{
			return arr[m];
		}
	}

	return -1;

}

int main(int argc, char *argv[])
{
	int key;
	int ret;
	int arr[MAX];//局部变量 => stack
	int *p = NULL;

	init(arr);
	show(arr);

	swap(arr);
	show(arr);

	printf("input find : ");
	scanf("%d", &key);

    /*
	 *ret = find(arr, key);
     */
	/*ret = my_bsearch(arr, 0, MAX - 1, key);*/
	p = (int *)bsearch(&key, arr, MAX, sizeof(int), cmp);

	if (p == NULL)
	{
		printf("no match info!\n");
	}
	else
	{
		printf("find : %d\n", *p);
	}
	return 0;
}


