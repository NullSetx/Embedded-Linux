#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int num;

	printf("input number : ");
	scanf("%d", &num);

	if (num >= 0)
	{
		printf("%d abs is %d\n", num, num);
	}
	else
	{
		printf("%d abs is %d\n", num, -num);
	}
	return 0;
}
