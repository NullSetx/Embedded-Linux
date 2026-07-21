#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int e = 123;//全局变量 RO
int ee;//BSS

int main(void)
{
	static int a = 123;
	int *p = NULL, *q = NULL;

	printf("&a : %p\n", &a);
	//heap 由小到大分配
	p = (int *)malloc(100);

	q = (int *)malloc(200);

	printf("p : %p\n", p);
	printf("q : %p\n", q);

	printf("&e : %p\n", &e);
	printf("&ee : %p\n", &ee);

	printf("const : %p\n", "hello");
	/*"hello"[0] = 'A';*/
	free(p);
	free(q);
	return 0;
}
