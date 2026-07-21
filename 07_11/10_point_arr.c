#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int a = 10;
	/*char ch = 'A';*/
	int *q = &a;
	int arr[5] = {1,2,3,4,5};
	int brr[2][3] = {11,22,33,44,55};

	int *p[5] = {&a, NULL, q, arr, brr[0]};//指针数组

	printf("sizeof(p) : %d\n", sizeof(p));

	printf("&a : %p\n", &a);
	printf("p[0] : %p\n", p[0]);
	printf("*p[0] : %d\n", *p[0]);
	printf("arr : %p\n", arr);
	printf("p[3] : %p\n", p[3]);

	for (i = 0; i < 5; i++)
	{
		/*printf("%d ", *(p[3] + i));*/
		printf("%d ", p[3][i]);
	}
	putchar(10);
	return 0;
}
