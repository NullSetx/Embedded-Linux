#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i, j;
	int arr[2][3] = {1,2,3,4,5,6};
	int (*p)[3] = NULL; //数组指针 首先是指针，再是数组，说明这个指针指向的是一个数组(多维数组)的地址

	printf("sizeof(p) : %d\n", sizeof(p));
	/*p = arr;*/

	p = arr;

	printf("p : %p p + 1 : %p\n", p, p + 1);
	printf("arr : %p arr + 1 : %p\n", arr, arr + 1);
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 3; j++)
		{
			/*printf("%d ", *(*(arr + i) + j));*/
			/*printf("%d ", *(*(p + i) + j));*/
			/*printf("%d ", p[i][j]);*/
			/*printf("%d ", *(p[i] + j));*/
			printf("%d ", (*(p + i))[j]);

		}
		putchar(10);
	}

	return 0;
}
