#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ROW 2
#define COL 3

void test(int arr[][COL])
{

}

int main(void)
{
	int i, j;

	int arr[ROW][COL] = {1,2,3,4,5,6};// sizeof(type) * row_index * col_index

	//数组名 arr &arr
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			printf("%d => %p\n", arr[i][j], &arr[i][j]);
		}
	}
	printf("==========main ===========\n");
	//&arr : 表示整个数组的首地址，+1偏移整个数组大小
	printf("&arr : %p &arr + 1 : %p\n", &arr, &arr + 1);
	//arr  : 表示行的首地址， +1偏移一行的大小
	printf("arr : %p arr + 1 : %p\n", arr, arr + 1);
	//arr[0] : 表示列的首地址, +1 偏移一列的大小
	printf("arr[0] : %p arr[0] + 1 : %p\n", arr[0], arr[0] + 1);
	//&arr[0][0] :表示第一个数据元素的地址 +1偏移数据类型的大小
	printf("&arr[0][0] : %p &arr[0][0] + 1 : %p\n", &arr[0][0], &arr[0][0] + 1);
	printf("==========test ===========\n");
	test(arr);
	return 0;
}
