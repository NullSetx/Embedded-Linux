#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define MAX 10

int main(int argc, char *argv[])
{
	int i;
	int arr[MAX];

	for (i = 0; i < MAX; i++)
	{
		arr[i] = rand() % 100;
	}
	for (i = 0; i < MAX; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar(10);
	return 0;
}
