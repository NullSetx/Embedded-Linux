#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>


void test(void)
{
	printf("this is test!\n");
	return ; //表示调用函数结束，并不表示程序的结束
	//临时堆栈的释放
}

int main(int argc, char *argv[])
{
	printf("main start ...\n");
	test();

	printf("main end ...\n");
	return 0;//表示进程的结束
}
