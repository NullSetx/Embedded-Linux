#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int sum;

	printf("input sum : ");
	scanf("%d", &sum);

	if (sum >= 90)
	{
		printf("A!\n");
	}
	else if (sum >= 75)
	{
		printf("B!\n");
	}
	else if (sum >= 60)
	{
		printf("C!\n");
	}
	else
	{
		printf("D!\n");
	}
	return 0;
}
