#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//1 值传递
//2 地址传递   => 是否需要修改变量
void init_01(int *p)
{
	printf("init_01 => &p : %p p : %p\n", &p, p);
	p = (int *)malloc(sizeof(int));
	if (p == NULL)
	{
		printf("malloc false!\n");
		return ;
	}
	printf("malloc success!\n");
}

int *init_02(void)
{
	int *p = NULL;//局部变量  &p p

	p = (int *)malloc(sizeof(int));
	if (p == NULL)
	{
		printf("malloc false!\n");
		return NULL;
	}
	printf("malloc success!\n");

	return p;
}

int main(void)
{
	int *p = NULL;

	printf("main => &p : %p p : %p\n", &p, p);
	//让子函数帮忙申请空间
	//1 传参
	//2 返回

	//p = (int *)malloc(sizeof(int));

	init_01(p);
	/*p = init_02();*/

	*p = 123;


	return 0;
}
