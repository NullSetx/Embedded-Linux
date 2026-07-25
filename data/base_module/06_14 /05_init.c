#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	//定义并初始化
	/*int arr[5] = {1,2,3,4,5};*/
	//定义
/*
 *    int arr[5];
 *
 *    int arr[5] = {123};//如果定义的时候赋值，则未赋值数据为0
 *
 *    //脱离开定义的赋值
 *    arr[0] = 123;
 */

	/*int arr[5] = {};//清空数组*/

	//如果定义的时候未指定小标，则一定要初始化，而数组个数，由初始化数据个数来决定。
	//
	/*int arr[] = {123};*/

	//指定小标初始化
	int arr[5] = {[2] = 123, 789, [1] = 456};

	for (i = 0; i < 5; i++)
	{
		printf("arr[%d] : %d\n", i, arr[i]);
	}
	return 0;
}
