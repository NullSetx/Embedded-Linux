#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a = 10;
	int b = 20;
	//常量指针 ： 不可以修改指针所指向的数据的值
	/*const int *p = &a; //只能修改指针的值 但不可以修改指针指向的值*/
	//int const *p = &a; 同上

	//指针常量：不可以修改指针的值 可以修改指针所指向的数据的值
	/*int * const p = &a;*/

	//常量指针常量 ： 指针的值和指针所指向的值都不可以修改
	const int * const p = &a;


	p = &b;

	*p = 30;

	return 0;
}
