#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

const int e = 1122; //常量

int main(int argc, char *argv[])
{
	const int a = 10; //伪常量
	
	*((int *)&a) = 20;

	printf("a : %d\n", a);

	*((int *)&e) = 3344;
	printf("e : %d\n", e);
	return 0;
}
