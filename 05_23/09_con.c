#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a, b;
	int max;

	printf("input two number : ");
	scanf("%d%d", &a, &b);

	printf("a: %d b : %d\n", a, b);

	max = a > b ? a : b;

	printf("max : %d\n", max);
	return 0;
}
