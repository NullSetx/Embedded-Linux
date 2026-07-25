#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int i;
	int count = 0;

	//随机数种子
	srand(time(NULL));

	while (1)
	{
		printf("第 %2d 期 ：", ++count);
		for (i = 0; i < 7; i++)
		{
			if (i == 6)
			{
				printf(" + \033[31m%2d\033[0m\n", rand() % 16 + 1);
			}
			else
			{
				printf("%2d ", rand() % 32 + 1);
			}
		}
		sleep(3);
	}
	return 0;
}
