#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char *c = NULL;
	int *i = NULL;

	void *v = NULL;

	printf("c : %p c + 1: %p\n", c, c + 1);
	printf("i : %p i+ 1: %p\n", i, i + 1);
	printf("v : %p v+ 1: %p\n", v, v + 1);
	return 0;
}
