#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int e = 123;//全局变量 RO
int ee;//BSS

int main(void)
{
	int a = 123;
	int *p = NULL;//局部变量

	//heap 由小到大分配 => 动态内存
	p = (int *)malloc(100);  //stack -> heap

	printf("&p : %p\n", &p);
	printf("p : %p\n", p);


	p = &a;//stack -> stack

	p = &e; //stack ->ro

	p = &ee;//stack -> BSS

	p = (void *)123; //stack -> const

	free(p);
	return 0;
}
