#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i, j;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j <= i; j++)
		{
			/*printf("* ");*/
			printf("hello ");
		}
		putchar(10);
	}
	return 0;
}
