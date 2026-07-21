#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
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

	while (1)
	{
		putchar(getchar());
	}

	//打开回显和缓冲区
	system("stty echo");
	system("stty icanon");



	return 0;
}
