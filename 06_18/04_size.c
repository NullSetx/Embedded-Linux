#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ROW 5
#define COL 8

void test(int arr[][COL])
{
	printf("sizeof(arr) : %d\n", sizeof(arr));//数组空间大小
	printf("szieof(arr[0]) : %d\n", sizeof(arr[0]));//行空间大小
	printf("sizeof(arr[0][0]) : %d\n", sizeof(arr[0][0]));

	printf("row : %d\n", sizeof(arr) / sizeof(arr[0]));
	printf("col : %d\n", sizeof(arr[0]) / sizeof(arr[0][0]));
	printf("size : %d\n", sizeof(arr) / sizeof(arr[0][0]));

}

int main(void)
{
	int arr[ROW][COL];// sizeof(type) * row_index * col_index

	printf("==========main ===========\n");
	printf("sizeof(arr) : %d\n", sizeof(arr));//数组空间大小
	printf("szieof(arr[0]) : %d\n", sizeof(arr[0]));//行空间大小
	printf("sizeof(arr[0][0]) : %d\n", sizeof(arr[0][0]));

	printf("row : %d\n", sizeof(arr) / sizeof(arr[0]));
	printf("col : %d\n", sizeof(arr[0]) / sizeof(arr[0][0]));
	printf("size : %d\n", sizeof(arr) / sizeof(arr[0][0]));

	printf("==========test ===========\n");
	test(arr);
	return 0;
}
