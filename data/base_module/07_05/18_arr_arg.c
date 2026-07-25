#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int *show(int *arr)//临时变量
{
	arr[0] = 123;
	return arr;
}

int main(void)
{
	int i;
	int arr[5] = {1,2,3,4,5};
	int *p = NULL;


	p = show(arr);

	for (i = 0; i < 5; i++)
	{
		printf("%d ", p[i]);
	}
	putchar(10);
	return 0;
}
