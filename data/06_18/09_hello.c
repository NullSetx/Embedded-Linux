#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int x, y;

	printf("input show x and y : ");
	scanf("%d%d", &x, &y);
	system("clear");//清屏函数
	//VT : 就是终端简单控制 前缀\033
	printf("\033[%d;%dHhello!\n", x, y);
	printf("\033[31mh\033[32me\033[33ml\033[34;46mlo\033[0m\n");
	return 0;
}
