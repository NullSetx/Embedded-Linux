#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int num;
	float price = 0.0;

	printf("input numbers : ");
	scanf("%d", &num);

	if (num >= 3 && num < 5)
	{
		printf("0.95\n");
		price = num * 1999 * 0.95;
	}
	else if (num >= 5 && num < 10)
	{
		
		price = num * 1999 * 0.9;
	}
	else if (num >= 10 && num < 15)
	{
		printf("0.85\n");
		price = num * 1999 * 0.85;
	}
	else if (num >= 15 && num < 20)
	{
		price = num * 1999 * 0.8;
	}
	else if (num >= 20)
	{
		price = num * 1999 * 0.7;
	}
	else
	{
		price = num * 1999;
	}

	printf("buy number %d, all price : %.2f\n", num, price);

	return 0;
}
