#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char ch;
	char key[8];
	int ret;
/*
 *    char ch;
 *
 *    ch = getchar();
 *
 *    putchar(ch);
 */
	//getchar() 接受一个字符
	//putchar() 输出一个字符
	//
	//关闭回显
	system("stty -echo");
	//关闭缓冲区
	system("stty -icanon");

	system("clear");

	while (1)
	{
		ret = read(0, key, sizeof(key));

		if (key[0] == 119 || key[2] == 65)
		{
			printf("hello");
			printf("\033[A");
		}
		else if (key[0] == 27 && ret == 1)
		{
			break;
		}
		else if (key[0] == 's' || key[2] == 66)
		{
			printf("\033[B");
		}
		else if (key[0] == 'd' || key[2] == 67)
		{
			printf("\033[C");
		}
		else if (key[0] == 'a' || key[2] == 68)
		{
			printf("\033[D");
		}
		else 
		{
			putchar(ch);
		}
		memset(key, 0, sizeof(key));
		fflush(NULL);
	}

	//打开回显和缓冲区
	system("stty echo");
	system("stty icanon");



	return 0;
}
