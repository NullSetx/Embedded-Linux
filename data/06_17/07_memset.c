#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int arr[5] = {123,34543, 54, 534,564};

	for (i = 0; i < 5; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar(10);

	memset(arr, 0xff, sizeof(arr));
	for (i = 0; i < 5; i++)
	{
		printf("%#x ", arr[i]);	
	}
	putchar(10);

	return 0;
}
