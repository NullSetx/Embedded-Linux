#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a;

	a = (10, 20), 30;

	printf("a : %d\n", a);
	return 0;
}
