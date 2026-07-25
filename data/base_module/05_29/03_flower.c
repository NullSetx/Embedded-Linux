#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int num = 1000;
	int sum = 0, bit, tmp;

	while (--num)
	{
		tmp = num;
		while (tmp)
		{
			bit = tmp % 10;
			sum += bit * bit * bit;

			tmp /= 10;
		}
		if (sum == num)
		{
			printf("%d\n", num);
		}	
		sum = 0;
	}
	return 0;
}
