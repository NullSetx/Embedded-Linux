#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	//数组表示地址
	int arr[5] = {1,2,3,4,5};

	for (i = 0; i < 5; i++)
		printf("%p : %d\n", &arr[i], arr[i]);

	printf("===============\n");
	printf("input number : ");
	/*scanf("%d", &arr[0]);*/
	/*scanf("%d", arr);*/
	scanf("%d", &arr);
	for (i = 0; i < 5; i++)
	{
		/*printf("%p : %d\n", &arr[0] + i, *(&arr[0] + i));*/
		printf("%p : %d\n", arr + i, *(arr + i));
	}
	printf("===============\n");
	//数组变量 ： arr
    /*
	 *printf("arr : %p\n", arr);
	 *printf("&arr : %p\n", &arr);
	 *printf("&arr[0] : %p\n", &arr[0]);
     */
	//&arr : 表示整个数组首地址 +1偏移整个数组大小
	printf("&arr : %p &arr + 1 : %p\n", &arr, &arr + 1);
	//arr : 表示数据元素的首地址，+1偏移数据元素的大小
	printf("arr : %p arr + 1 : %p\n", arr, arr + 1);
	return 0;
}
