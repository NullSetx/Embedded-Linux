#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i;

	while (0)
	{
		for (i = 0; i < 10; i++)
		{
			if (i == 5)
			{
				/*break;*/
				continue;
			}
			printf("%d ", i);
		}
		putchar(10);
	}
	return 0;
}
