#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i, j;

	for (j = 0; j < 20; j++)
	{
		printf("\033[5;10H");
		for (i = 0; i <= j; i++)
		{
			printf("=");
		}
		printf(">");
		printf("\033[5;32H %d%%", i * 5);
		usleep(300000);
		fflush(NULL);
	}
	return 0;
}
