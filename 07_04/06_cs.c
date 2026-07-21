#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char ch;
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
		ch = getchar();
		if (ch == 119)
		{
			printf("hello");
			printf("\033[A");
		}
		else if (ch == 's')
		{
			printf("\033[B");
		}
		else if (ch == 'd')
		{
			printf("\033[C");
		}
		else if (ch == 'a')
		{
			printf("\033[D");
		}
		else 
		{
			putchar(ch);
		}
	}

	//打开回显和缓冲区
	system("stty echo");
	system("stty icanon");



	return 0;
}
