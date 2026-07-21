#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a = 10;
	int **p = (int **)&a;

	printf("&a : %p\n", &a);
	printf("p : %p\n", p);
	printf("*p : %p\n", *p);
	/*printf("**p : %d\n", **p);*/

	return 0;
}
