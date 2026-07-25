#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5

int main(void)
{
	int i;
	int arr[MAX];//40
    /*
	 *int arr[i];//
	 *printf("arr[i - 1] : %d\n", arr[i - 1]);
     */
	
	//求数组空间大小
	printf("sizeof(arr) ：%d\n", sizeof(arr));
	printf("sizeof(arr[0]) : %d\n", sizeof(arr[0]));
	printf("num : %d\n", sizeof(arr) / sizeof(arr[0]));
	return 0;
}
