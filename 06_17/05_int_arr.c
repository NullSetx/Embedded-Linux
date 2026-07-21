#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char dest[128] = {}, src[128] = "hello";
	int i;
	int arr[5] = {1,2,3,4,5};
	int brr[5] = {};

	for (i = 0; i < 5; i++)
	{
		printf("%d ", brr[i]);
	}
	putchar(10);
	/*memcpy(brr, arr, sizeof(arr));*/
	memmove(brr, arr, sizeof(arr));
	/*strcpy(brr, arr);*/
	
	for (i = 0; i < 5; i++)
	{
		printf("%d ", brr[i]);
	}
	putchar(10);

	/*memcpy(dest, src, strlen(src) + 1);*/
	memmove(dest, src, strlen(src) + 1);
	printf("dest : %s\n", dest);
	printf("src : %s\n", src);
	return 0;
}
