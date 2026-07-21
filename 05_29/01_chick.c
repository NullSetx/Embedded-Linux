#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i, j, k;

	for (i = 0; i <= 20; i++)
	{
		for (j = 0; j <= 33; j++)
		{
			for (k = 0; k <= 100; k++)
			{
				if (i + j + k == 100 && i * 5 + j * 3 + k / 3 == 100 && k % 3 == 0)
				{
					printf("公鸡: %d 母鸡: %d 小鸡: %d\n", i, j, k);
				}
			}
		}
	}
	return 0;
}
