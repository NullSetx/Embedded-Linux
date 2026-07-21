#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
	int num;

	while (1)
	{
		//printf是把数据输出到缓存中，如果缓存满了，则再由缓存输出到显示器上   或者  遇到\n 一样会输出到显示器
		//printf函数叫行缓存函数
		/*if ((num = rand()) < 100)*/
		/*printf("%d ", rand() % 100);*/
		printf("%d ", rand() % 50 + 50);
		sleep(1);//1秒
		//手动刷新缓冲区
		//缓冲区分两种：输入缓冲区 和 输出缓冲区
		//刷新输出缓冲区
		/*fflush(stdout);*/
		/*fflush(stdin);*/
		fflush(NULL);//表示输入输出都会刷新

	}
	return 0;
}
