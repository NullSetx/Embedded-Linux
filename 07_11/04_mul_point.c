#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a = 10, b = 20;
	int *q = &a;
	int **p = NULL;//保存地址 一般保存一级指针的地址

	//p 是指针变量
	p = &q;

	q = &b;

	**p = 123;

	/**q = 456;*/
	printf("&a : %p a : %d\n", &a, a);
	printf("&q : %p q : %p *q : %d\n", &q, q, *q);
	printf("&p : %p p : %p *p : %p **p : %d\n", &p, p, *p, **p);
	return 0;
}
