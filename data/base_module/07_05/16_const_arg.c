#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void test(const int *a)
{
	/**a = 123;*/

	*(int *)a = 123;
}
int main(void)
{
	int a = 10;

	test(&a);

	return 0;
}
