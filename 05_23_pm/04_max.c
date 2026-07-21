#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int num1, num2;
	int max;

	printf("input two numbers : ");
	scanf("%d%d", &num1, &num2);

	printf("num1 : %d num2 : %d\n", num1, num2);

	if (num1 >= num2)
	{
		printf("max : %d\n", num1);
	}
	
	if (num1 < num2)
	{
		printf("max : %d\n", num2);
	}
	printf("=======================\n");
	max = num1;

	if (max < num2)
	{
		max = num2;
	}
	printf("max : %d\n", max);

	printf("=======================\n");
	if (num1 > num2)
	{
		printf("max : %d\n", num1);
	}
	else
	{
		printf("max : %d\n", num2);
	}

	return 0;
}
