#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;

	int *p = NULL;
	int arr[5] = {1,2,3,4,5};

	
	p = arr;
	p[0] = 123;

	p = p + 1;
	arr = arr + 1;

	for (i = 0; i < 5; i++)
	{
		/*printf("%d ", arr[i]);*/
		/*printf("%d ", p[i]);*/
		/*printf("%d ", *(p + i));*/
		printf("%d ", *(arr + i));
	}
	putchar(10);

	printf("sizeof(arr) : %d\n", sizeof(arr));
	printf("sizeof(p) : %d\n", sizeof(p));//20 4
	return 0;
}
