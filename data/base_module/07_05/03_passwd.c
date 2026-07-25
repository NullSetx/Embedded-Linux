#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i = 0;
	char buf[8];
	int ret;
	char passwd[64] = {};

	system("stty -echo -icanon");
	
	printf("input passwd : ");
	fflush(NULL);
	while (1)
	{
		ret = read(0, buf, sizeof(buf));
		if (ret == -1)
		{
			return -1;
		}
		else if (buf[0] == 27)
		{
			break;
		}
		else if (buf[0] == 127)
		{
			if (i == 0)
			{
				continue;
			}
			printf("\033[D");
			putchar(' ');
			printf("\033[D");
			i--;

		}
		else
		{
			printf("*");
			passwd[i++] = buf[0];
		}

		fflush(NULL);

	}
	passwd[i] = '\0';

	system("stty echo icanon");
	printf("passwd : %s\n", passwd);
	return 0;
}
