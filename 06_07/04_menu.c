#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void left_down(int line)
{
	int i, j;

	for (i = 0; i < line; i++)
	{
		for (j = 0; j <= i; j++)
		{
			printf("* ");
		}
		putchar(10);
	}
}

int main(void)
{
	int sel;
	int quit = 0;
	int line = 6;

	while (!quit)
	{
		system("clear");//清屏函数
		printf("0 set line\n");
		printf("1 left down\n");
		printf("2 left up\n");
		printf("3 right down\n");
		printf("4 right up\n");
		printf("5 exit\n");
		printf("input sel : ");
		scanf("%d", &sel);

		switch (sel)
		{
			case 0:
				printf("input line : ");
				scanf("%d", &line);
				break;
			case 1:
				left_down(line);
				/*printf("left down!\n");*/
				break;
			case 2:
				printf("left up!\n");
				break;
			case 3:
				printf("right down!\n");
				break;
			case 4:
				printf("right up!\n");
				break;
			case 5:
				printf("exit!\n");
				/*break;*/
				quit = 1;
				/*goto out;*/
				break;
		}
		getchar();
		getchar();
	}

	/*out:*/
	return 0;
}
