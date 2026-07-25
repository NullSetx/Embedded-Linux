#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

const int e = 123;//不可以修改

int main(int argc, char *argv[])
{
	const int a = 10;//伪常量

	*((int *)&a) = 20;

	printf("a : %d &a : %p\n", a, &a);

    /*
	 **((int *)&e) = 456;
	 *printf("e : %d\n", e);
     */
	getchar();
	return 0;
}
